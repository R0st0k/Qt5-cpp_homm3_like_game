#include "../headers/resourcebar.h"

ResourceBar::ResourceBar(){
    tree = new QLabel;
    tree->setText("0");
    tree->setMinimumSize(608, 25);
    tree->setStyleSheet("background-image: url(:/technical/images/technical/ResBar.png);"
                          "font: 12px Times New Roman;"
                          "color: white;"
                          "padding-left: 38px;"
                          "padding-bottom: 4px");
    mercury = new QLabel;
    mercury->setText("0");
    mercury->setMinimumSize(608, 25);
    mercury->setStyleSheet("font: 12px Times New Roman;"
                        "color: white;"
                        "padding-left: 120px;"
                        "padding-bottom: 4px");
    ore = new QLabel;
    ore->setText("0");
    ore->setMinimumSize(608, 25);
    ore->setStyleSheet("font: 12px Times New Roman;"
                        "color: white;"
                        "padding-left: 207px;"
                        "padding-bottom: 4px");
    sulfur = new QLabel;
    sulfur->setText("0");
    sulfur->setMinimumSize(608, 25);
    sulfur->setStyleSheet("font: 12px Times New Roman;"
                        "color: white;"
                        "padding-left: 291px;"
                        "padding-bottom: 4px");
    crystal = new QLabel;
    crystal->setText("0");
    crystal->setMinimumSize(608, 25);
    crystal->setStyleSheet("font: 12px Times New Roman;"
                        "color: white;"
                        "padding-left: 372px;"
                        "padding-bottom: 4px");
    gem = new QLabel;
    gem->setText("0");
    gem->setMinimumSize(608, 25);
    gem->setStyleSheet("font: 12px Times New Roman;"
                        "color: white;"
                        "padding-left: 460px;"
                        "padding-bottom: 4px");
    gold = new QLabel;
    gold->setText("0");
    gold->setMinimumSize(608, 25);
    gold->setStyleSheet("font: 12px Times New Roman;"
                        "color: white;"
                        "padding-left: 545px;"
                        "padding-bottom: 4px");
}

ResourceBar::~ResourceBar(){
    delete tree;
    delete mercury;
    delete ore;
    delete sulfur;
    delete crystal;
    delete gem;
    delete gold;
}
