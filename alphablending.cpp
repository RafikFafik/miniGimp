#include "alphablending.h"
#include "ui_alphablending.h"

AlphaBlending::AlphaBlending(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlphaBlending)
{
    ui->setupUi(this);
    img = new QImage(ui->frame->width(), ui->frame->height(), QImage::Format_RGB32);
    Pixel::clear(img);
    imgs.clear();
    loadImages();
    updateGui();
    layersWalk();
//    prepareMap();
}

AlphaBlending::~AlphaBlending()
{
    delete ui;
}
void AlphaBlending::loadImages()
{
    foreach(const QString &image, QDir(":/pictures/").entryList()) {
        ui->images->addItem(image);
        ImageData *imageData = new ImageData;
        imageData->image = new QImage(":/pictures/" + image);
        imageData->image->scaled(500, 500, Qt::KeepAspectRatio);
        imageData->value = 100;
        imageData->active_mode = 0;
        imageData->visible = true;
        imageData->filename = image;
        imgs.push_back(imageData);
    }
}
void AlphaBlending::updateGui()
{
    int active_gui = ui->images->currentIndex();
    ImageData *activePhoto = imgs.at(active_gui);
    ui->mode->setCurrentIndex(activePhoto->active_mode);
    ui->value->setValue(activePhoto->value);
    ui->visibility->setChecked(activePhoto->visible);
}
void AlphaBlending::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(0, 0, *img);
}
void AlphaBlending::layersWalk()
{
    Pixel::clear(img);
    for(auto it = imgs.rbegin(); it != imgs.rend(); it++) {
        blend(*it);
    }
    update();
}
void AlphaBlending::blend(ImageData *foreground)
{
    if(!foreground->visible)
        return;
    double alpha = (double)foreground->value / 100;
    Color *color = new Color;
    unsigned char *current = foreground->image->bits();
    int mode = foreground->active_mode;
    unsigned char *ptr = img->bits();
    int width = ui->frame->width();
    for(int i = 0; i < ui->frame->height(); i++) {
        for(int j = 0; j < ui->frame->width(); j++) {
//            fg = Pixel::getPixelColor(foreground->image, Point(j, i));
//            bg = Pixel::getPixelColor(img, Point(j, i));
//            fg = fg * alpha;
//            bg = bg * beta;
//            result = fg + bg;
//            Pixel::setPixelColor(img, Point(j, i), result);
            color->red = switchBlendMode(ptr[width * 4 * i + 4 * j + 2],current[width * 4 * i + 4 * j + 2],  mode);
            color->green = switchBlendMode(ptr[width * 4 * i + 4 * j + 1],current[width * 4 * i + 4 * j + 1],  mode);
            color->blue = switchBlendMode(ptr[width * 4 * i + 4 * j], current[width * 4 * i + 4 * j], mode);
            ptr[width * 4 * i + 4 * j + 2] = alpha * color->red + (1 - alpha) * ptr[width * 4 * i + 4 * j + 2];
            ptr[width * 4 * i + 4 * j + 1] = alpha * color->green + (1 - alpha) * ptr[width * 4 * i + 4 * j + 1];
            ptr[width * 4 * i + 4 * j] = alpha * color->blue + (1 - alpha) * ptr[width * 4 * i + 4 * j];
        }
    }
    delete color;
}


void AlphaBlending::on_images_currentIndexChanged(int index)
{
    if(imgs.empty())
        return;
    ImageData *imageData = imgs.at(index);
    ui->visibility->setChecked(imageData->visible);
    ui->value->setValue(imageData->value);
    ui->mode->setCurrentIndex(imageData->active_mode);
    layersWalk();
}

void AlphaBlending::on_visibility_stateChanged(int visible) {
    if(imgs.empty())
        return;
    ImageData *imageData = imgs.at(ui->images->currentIndex());
    imageData->visible = visible;
    layersWalk();
}

void AlphaBlending::on_value_valueChanged(int value) {
    if(imgs.empty())
        return;
    ImageData *imageData = imgs.at(ui->images->currentIndex());
    imageData->value = value;
    layersWalk();
}
void AlphaBlending::on_mode_currentIndexChanged(int mode) {
    if(imgs.empty())
        return;
    ImageData *imageData = imgs.at(ui->images->currentIndex());
    imageData->active_mode = mode;
    layersWalk();
}

unsigned char AlphaBlending::switchBlendMode(unsigned char background, unsigned char foreground, int mode) {
    switch(mode) {
    case 1:
        return AlphaBlending::multiply(background, foreground);
        break;
    case 2:
        return AlphaBlending::screen(background, foreground);
        break;
    case 3:
        return AlphaBlending::overlay(background, foreground);
        break;
    case 4:
        return AlphaBlending::darken(background, foreground);
        break;
    case 5:
        return AlphaBlending::lighten(background, foreground);
        break;
    case 6:
        return AlphaBlending::difference(background, foreground);
        break;
    default:
        return foreground;
    }
}

unsigned char AlphaBlending::multiply(unsigned char bg, unsigned char fg) {
    return (fg * bg) >> 8;
}
unsigned char AlphaBlending::screen(unsigned char bg, unsigned char fg){
    return (255 - ((255 - bg) * (255 - fg) >> 8));
}
unsigned char AlphaBlending::overlay(unsigned char bg, unsigned char fg){
    return (bg < 128) ? bg * fg >> 8 : 255 - ((255 - bg) * (255 - fg) >> 7);
}
unsigned char AlphaBlending::darken(unsigned char bg, unsigned char fg){
    return (bg < fg ? bg : fg);
}
unsigned char AlphaBlending::lighten(unsigned char bg, unsigned char fg){
    return (bg < fg ? fg : bg);
}
unsigned char AlphaBlending::difference(unsigned char bg, unsigned char fg){
    return (abs(bg - fg));
}


