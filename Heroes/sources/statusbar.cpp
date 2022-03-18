#include "../headers/statusbar.h"

StatusBar::StatusBar(){
    this->setObjectName("statusBar");
    this->setMinimumSize(608, 20);
    this->setAlignment(Qt::AlignCenter);
    this->setStyleSheet("background-image: url(:/technical/images/technical/StatusBar.png);"
                        "font: 12px Times New Roman;"
                        "color: white;");
}
