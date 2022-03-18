#include "../headers/gamemodel.h"

GameModel::GameModel(){
    originalField = &Field::getField();
    heroes = new Heroes;
    colors = new Color[4];
    colors[1].heroes = &heroes->allHeroes[0];
    for(int i = 0; i < 6; i++)
        colors[1].resources[i] = 0;
    colors[1].color = 1;
    gameTimer = new QTimer();
    gameTimer->start(100);
    log = new FileColorLogger(2);
    command = new Command;
    subscribe(log);
    loadImage();
}

GameModel::~GameModel(){
    for(int i = 0; i < 9; i++)
        delete[] frameSpace[i];
    delete[] frameSpace;
    for(int i = 0; i < 2; i++)
        delete[] terrain[i];
    delete[] terrain;
    delete gameTimer;
    delete[] colors;
    delete enemies;
    delete heroes;
    delete log;
    delete command;
    delete originalField;
}

void GameModel::loadImage(){
    frameSpace = new QPixmap* [9];
    for(int i = 0; i < 9; i++){
        frameSpace[i] = new QPixmap [4];
        for(int j = 0; j < 4; j++){
            int puzzleCount = (i*4)+j+1;
            QString path = ":/frameSpace/images/frameSpace/EDG"; path.append(48 + (int)(puzzleCount / 10)); path.append(48 + (puzzleCount % 10)); path.append(".png");
            frameSpace[i][j].load(path);
        }
    }
    terrain = new QPixmap* [2];
    for(int i = 0; i < 2; i++)
        terrain[i] = new QPixmap [10];
    for(int i = 0; i < 10; i++){
        QString pathGr = ":/terrains/images/terrains/tgrb00"; pathGr.append(48 + i); pathGr.append(".png");
        QString pathDt = ":/terrains/images/terrains/trob00"; pathDt.append(48 + i); pathDt.append(".png");
        terrain[0][i].load(pathGr);
        terrain[1][i].load(pathDt);
    }
}

void GameModel::ReadField(QString path) {
    QFile map(path);

    bool correct = true;
    bool temp;

    if (!map.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    FieldIterator iter;
    size = iter.getSize();
    emit signalSetFieldSize(size);

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            iter.current(i, j).passability = 2;
            iter.current(i, j).terrain = 9;
            iter.current(i, j).terrainPatern = (i + 2) % 4;
            iter.current(i, j).terrainRotate = (j + 2) % 4;
            iter.current(i, j).isFrame = true;
            if(7 < i && i < size-8 && j == 7)
                j = size - 9;
        }
    }
    for(int j = 8; j < size-8; j++){
        if(j == 8 || j == size - 9){
            iter.current(8, j).passability = 2;
            iter.current(8, j).terrain = 9;
            iter.current(8, j).terrainPatern = 4;
            iter.current(8, j).isFrame = true;
            iter.current(size-9, j).passability = 2;
            iter.current(size-9, j).terrain = 9;
            iter.current(size-9, j).terrainPatern = 4;
            iter.current(size-9, j).isFrame = true;
            if(j == 8){
                iter.current(8, j).terrainRotate = 0;
                iter.current(size-9, j).terrainRotate = 3;
            }
            if(j == size - 9){
                iter.current(8, j).terrainRotate = 1;
                iter.current(size-9, j).terrainRotate = 2;
            }
            continue;
        }
        iter.current(8, j).passability = 2;
        iter.current(8, j).terrain = 9;
        iter.current(8, j).terrainPatern = 5;
        iter.current(8, j).terrainRotate = (j - 1) % 4;
        iter.current(8, j).isFrame = true;
        iter.current(size-9, j).passability = 2;
        iter.current(size-9, j).terrain = 9;
        iter.current(size-9, j).terrainPatern = 7;
        iter.current(size-9, j).terrainRotate = (4 - (j % 4)) % 4;
        iter.current(size-9, j).isFrame = true;
    }
    for(int i = 9; i < size-9; i++){
        iter.current(i, size-9).passability = 2;
        iter.current(i, size-9).terrain = 9;
        iter.current(i, size-9).terrainPatern = 6;
        iter.current(i, size-9).terrainRotate = (i - 1) % 4;
        iter.current(i, size-9).isFrame = true;
        iter.current(i, 8).passability = 2;
        iter.current(i, 8).terrain = 9;
        iter.current(i, 8).terrainPatern = 8;
        iter.current(i, 8).terrainRotate = (4 - (i % 4)) % 4;
        iter.current(i, 8).isFrame = true;
    }

    char* c = new char;
    iter.startRead();
    GrassFactory factory;
    while (!iter.isDoneRead()) {
        map.getChar(c);
        map.getChar(c);
        iter.current().terrain = int(*c) - 48;
        map.getChar(c);
        iter.current().terrainPatern = int(*c) - 48;
        map.getChar(c);
        iter.current().terrainRotate = int(*c) - 48;
        map.getChar(c);
        iter.current().object = int(*c) - 48;
        map.getChar(c);
        iter.current().objectPatern1 = int(*c) - 48;
        map.getChar(c);
        iter.current().objectPatern2 = int(*c) - 48;
        map.getChar(c);
        switch (iter.current().object) {
        case 0:
            break;
        case 1:
            factory.createStone(iter);
            iter.current().objectItem->subscribe(log);
            break;
        case 2:
            if(iter.current().objectPatern1 == 1)
                factory.createCastle(iter, iter.current().objectPatern2);
            if(iter.current().objectPatern1 == 7)
                factory.createStronghold(iter, iter.current().objectPatern2);
            if(iter.current().objectPatern1 == 8)
                factory.createFortress(iter, iter.current().objectPatern2);
            iter.current().objectItem->subscribe(log);
            break;
        case 6:
            factory.createBonfire(iter);
            iter.current().objectItem->subscribe(log);
            break;
        default:
            iter.current().passability = 0;
            break;
        }
        iter.nextRead();
    }

    QStringList lineData = QString(map.readLine()).split(" ");
    colors[1].heroes->width = lineData[0].toInt(&temp); correct&=temp;
    colors[1].heroes->height = lineData[1].toInt(&temp); correct&=temp;
    emit signalSetStartCam(lineData[2].toInt(&temp), lineData[3].toInt(&temp)); correct&=temp;
    emit signalGoldChange(lineData[4].toInt(&temp)); correct&=temp;
    lineData = QString(map.readLine()).split(" ");
    enemies = new Enemy(lineData[0].toInt(&temp),lineData[1].toInt(&temp),lineData[2].toInt(&temp),lineData[3].toInt(&temp),lineData[4].toInt(&temp),lineData[5].toInt(&temp)); correct&=temp;
    enemies->Set_Aim(QPoint(14,19));
    isEnd = QString(map.readLine()).toUInt(&temp); correct&=temp;
    if(isEnd)
        emit signalEnd();
    if(!correct)
        emit signalUncorrectData();
    Snapshot* snap = new Snapshot(originalField, QPoint(colors[1].heroes->width, colors[1].heroes->height), QPoint(signalGetStartCam()), colors[1].gold,
                                  QPoint(enemies->curr_x1, enemies->curr_y1), QPoint(enemies->curr_x2, enemies->curr_y2), QPoint(enemies->curr_x3, enemies->curr_y3),
                                  isEnd);
    command->change(snap);
    map.close();
    delete c;
}

Cell GameModel::getCurrentCell(int i, int j){
    return originalField->getCell(i, j);
}

int** GameModel::pathFinder(QPoint object){
    int** path = new int* [size-18];
    for(int i = 0; i < size-18; i++)
        path[i] = new int [size-18];
    FieldIterator iter;
    iter.startRead();
    int i = 0;
    int j = 0;
    while(!iter.isDoneRead()){
        if(iter.current().passability == 1 || iter.current().passability == 2)
            path[i][j] = -1;
        else
            path[i][j] =  2000000000;
        j++;
        if(j == size-18){
            j = 0;
            i++;
        }
        iter.nextRead();
    }
    QPoint hero = QPoint(colors[1].heroes->height-9, colors[1].heroes->width-9);
    path[hero.x()][hero.y()] = 0;
    path[object.x()][object.y()] = 2000000000;
    QQueue<QPoint> queue;
    queue.enqueue(hero);
    while(!queue.isEmpty() && queue.head() != object){
        if(queue.head().x() - 1 >= 0 && path[queue.head().x()][queue.head().y()] + 100 < path[queue.head().x()-1][queue.head().y()]){
            path[queue.head().x()-1][queue.head().y()] = path[queue.head().x()][queue.head().y()] + 100;
            queue.enqueue(QPoint(queue.head().x()-1, queue.head().y()));
        }
        if(queue.head().x() + 1 < size-18 && path[queue.head().x()][queue.head().y()] + 100 < path[queue.head().x()+1][queue.head().y()]){
            path[queue.head().x()+1][queue.head().y()] = path[queue.head().x()][queue.head().y()] + 100;
            queue.enqueue(QPoint(queue.head().x()+1, queue.head().y()));
        }
        if(queue.head().y() - 1 >= 0 && path[queue.head().x()][queue.head().y()] + 100 < path[queue.head().x()][queue.head().y()-1]){
            path[queue.head().x()][queue.head().y()-1] = path[queue.head().x()][queue.head().y()] + 100;
            queue.enqueue(QPoint(queue.head().x(), queue.head().y()-1));
        }
        if(queue.head().y() + 1 < size-18 && path[queue.head().x()][queue.head().y()] + 100 < path[queue.head().x()][queue.head().y()+1]){
            path[queue.head().x()][queue.head().y()+1] = path[queue.head().x()][queue.head().y()] + 100;
            queue.enqueue(QPoint(queue.head().x(), queue.head().y()+1));
        }
        if(queue.head().x() - 1 >= 0 && queue.head().y() - 1 >= 0 && path[queue.head().x()][queue.head().y()] + 144 < path[queue.head().x()-1][queue.head().y()-1]){
            path[queue.head().x()-1][queue.head().y()-1] = path[queue.head().x()][queue.head().y()] + 144;
            queue.enqueue(QPoint(queue.head().x()-1, queue.head().y()-1));
        }
        if(queue.head().x() + 1 < size-18 && queue.head().y() + 1 < size-18 && path[queue.head().x()][queue.head().y()] + 144 < path[queue.head().x()+1][queue.head().y()+1]){
            path[queue.head().x()+1][queue.head().y()+1] = path[queue.head().x()][queue.head().y()] + 144;
            queue.enqueue(QPoint(queue.head().x()+1, queue.head().y()+1));
        }
        if(queue.head().x() - 1 >= 0 && queue.head().y() + 1 < size-18 && path[queue.head().x()][queue.head().y()] + 144 < path[queue.head().x()-1][queue.head().y()+1]){
            path[queue.head().x()-1][queue.head().y()+1] = path[queue.head().x()][queue.head().y()] + 144;
            queue.enqueue(QPoint(queue.head().x()-1, queue.head().y()+1));
        }
        if(queue.head().x() + 1 < size-18 && queue.head().y() - 1 >= 0 && path[queue.head().x()][queue.head().y()] + 144 < path[queue.head().x()+1][queue.head().y()-1]){
            path[queue.head().x()+1][queue.head().y()-1] = path[queue.head().x()][queue.head().y()] + 144;
            queue.enqueue(QPoint(queue.head().x()+1, queue.head().y()-1));
        }
        queue.dequeue();
    }
    return path;
}

QPixmap GameModel::pathArrowDrawer(QPoint prev, QPoint curr, QPoint next, bool enoughPoints){
    QPixmap answer(32, 32);
    answer.fill(Qt::transparent);
    int x = 0;
    int y = 0;
    if(!enoughPoints)
        x++;
    if(curr.isNull())
        return answer;
    if(prev.isNull())
        return QPixmap(":/technical/images/technical/endArrows.png").copy(x*CELL_SIZE, y*CELL_SIZE, CELL_SIZE, CELL_SIZE);
    switch (curr.x() - next.x()) {
    case 0:
        if(curr.y() - next.y() == 1){
            y = 1;
            if(curr.x() - prev.x() == 1)
                x = 0;
            if(curr.x() - prev.x() == 0)
                x = 1;
            if(curr.x() - prev.x() == -1)
                x = 2;
        }
        if(curr.y() - next.y() == -1){
            y = 5;
            if(curr.x() - prev.x() == -1)
                x = 0;
            if(curr.x() - prev.x() == 0)
                x = 1;
            if(curr.x() - prev.x() == 1)
                x = 2;
        }
        break;
    case 1:
        if(curr.y() - next.y() == 1){
            y = 2;
            if(curr.x() - prev.x() == 0 && curr.y() - prev.y() == -1)
                x = 0;
            if(curr.x() - prev.x() == -1 && curr.y() - prev.y() == -1)
                x = 1;
            if(curr.x() - prev.x() == -1 && curr.y() - prev.y() == 0)
                x = 2;
            if(curr.x() - prev.x() == 1 && curr.y() - prev.y() == -1){
                y = 1;
                x = 0;
            }
            if(curr.x() - prev.x() == -1 && curr.y() - prev.y() == 1){
                y = 3;
                x = 2;
            }
        }
        if(curr.y() - next.y() == 0){
            y = 3;
            if(curr.y() - prev.y() == -1)
                x = 0;
            if(curr.y() - prev.y() == 0)
                x = 1;
            if(curr.y() - prev.y() == 1)
                x = 2;
        }
        if(curr.y() - next.y() == -1){
            y = 4;
            if(curr.x() - prev.x() == -1 && curr.y() - prev.y() == 0)
                x = 0;
            if(curr.x() - prev.x() == -1 && curr.y() - prev.y() == 1)
                x = 1;
            if(curr.x() - prev.x() == 0 && curr.y() - prev.y() == 1)
                x = 2;
            if(curr.x() - prev.x() == -1 && curr.y() - prev.y() == -1){
                y = 3;
                x = 0;
            }
            if(curr.x() - prev.x() == 1 && curr.y() - prev.y() == 1){
                y = 5;
                x = 2;
            }
        }
        break;
    case -1:
        if(curr.y() - next.y() == 1){
            y = 0;
            if(curr.x() - prev.x() == 1 && curr.y() - prev.y() == 0)
                x = 0;
            if(curr.x() - prev.x() == 1 && curr.y() - prev.y() == -1)
                x = 1;
            if(curr.x() - prev.x() == 0 && curr.y() - prev.y() == -1)
                x = 2;
            if(curr.x() - prev.x() == 1 && curr.y() - prev.y() == 1){
                y = 7;
                x = 0;
            }
            if(curr.x() - prev.x() == -1 && curr.y() - prev.y() == -1){
                y = 1;
                x = 2;
            }
        }
        if(curr.y() - next.y() == -1){
            y = 6;
            if(curr.x() - prev.x() == 0 && curr.y() - prev.y() == 1)
                x = 0;
            if(curr.x() - prev.x() == 1 && curr.y() - prev.y() == 1)
                x = 1;
            if(curr.x() - prev.x() == 1 && curr.y() - prev.y() == 0)
                x = 2;
            if(curr.x() - prev.x() == -1 && curr.y() - prev.y() == 1){
                y = 5;
                x = 0;
            }
            if(curr.x() - prev.x() == 1 && curr.y() - prev.y() == -1){
                y = 7;
                x = 2;
            }
        }
        if(curr.y() - next.y() == 0){
            y = 7;
            if(curr.y() - prev.y() == 1)
                x = 0;
            if(curr.y() - prev.y() == 0)
                x = 1;
            if(curr.y() - prev.y() == -1)
                x = 2;
        }
        break;
    }
    if(!enoughPoints)
        x+= 3;
    return QPixmap(":/technical/images/technical/arrows.png").copy(x*CELL_SIZE, y*CELL_SIZE, CELL_SIZE, CELL_SIZE);
}

QPixmap GameModel::pathDrawer(QPoint start, int** path){
    while(!colors[1].heroes->path.isEmpty()){
        colors[1].heroes->path.pop();
    }
    QPixmap pathPixmap(CELL_SIZE*size, CELL_SIZE*size);
    pathPixmap.fill(Qt::transparent);
    QPoint end = QPoint(colors[1].heroes->height-9, colors[1].heroes->width-9);
    QPainter pathPainter(&pathPixmap);
    QPoint prev;
    QPoint curr;
    QPoint next = start;
    while(next != end){
        pathPainter.drawPixmap((curr.y()+9)*CELL_SIZE, (curr.x()+9)*CELL_SIZE, pathArrowDrawer(prev, curr, next, colors[1].heroes->move - path[curr.x()][curr.y()]>= 0));
        if(next.x() - 1 >= 0 && path[next.x()][next.y()] - 100 == path[next.x()-1][next.y()]){
            prev = curr;
            curr = next;
            next.rx()--;
            continue;
        }
        if(next.x() + 1 < size-18 && path[next.x()][next.y()] - 100 == path[next.x()+1][next.y()]){
            prev = curr;
            curr = next;
            next.rx()++;
            continue;
        }
        if(next.y() - 1 >= 0 && path[next.x()][next.y()] - 100 == path[next.x()][next.y()-1]){
            prev = curr;
            curr = next;
            next.ry()--;
            continue;
        }
        if(next.y() + 1 < size-18 && path[next.x()][next.y()] - 100 == path[next.x()][next.y()+1]){
            prev = curr;
            curr = next;
            next.ry()++;
            continue;
        }
        if(next.x() - 1 >= 0 && next.y() - 1 >= 0 && path[next.x()][next.y()] - 144 == path[next.x()-1][next.y()-1]){
            prev = curr;
            curr = next;
            next.rx()--;
            next.ry()--;
            continue;
        }
        if(next.x() + 1 < size-18 && next.y() + 1 < size-18 && path[next.x()][next.y()] - 144 == path[next.x()+1][next.y()+1]){
            prev = curr;
            curr = next;
            next.rx()++;
            next.ry()++;
            continue;
        }
        if(next.x() - 1 >= 0 && next.y() + 1 < size-18 && path[next.x()][next.y()] - 144 == path[next.x()-1][next.y()+1]){
            prev = curr;
            curr = next;
            next.rx()--;
            next.ry()++;
            continue;
        }
        if(next.x() + 1 < size-18 && next.y() - 1 >= 0 && path[next.x()][next.y()] - 144 == path[next.x()+1][next.y()-1]){
            prev = curr;
            curr = next;
            next.rx()++;
            next.ry()--;
            continue;
        }
    }
    pathPainter.drawPixmap((curr.y()+9)*CELL_SIZE, (curr.x()+9)*CELL_SIZE, pathArrowDrawer(prev, curr, next, colors[1].heroes->move - path[curr.x()][curr.y()]>= 0));
    pathPainter.end();
    for(int i = 0; i < size-18; i++)
        delete[] path[i];
    delete[] path;
    return pathPixmap;
}

QPixmap GameModel::fullMapDraw(){
    FieldIterator iter;
    QPixmap fullMap(CELL_SIZE*iter.getSize(), CELL_SIZE*iter.getSize());
    QPainter fullMapPainter(&fullMap);
    int x = 0;
    int y = 0;
    iter.startDraw();
    while(!iter.isDoneDraw()){
        if(iter.current().isFrame)
            fullMapPainter.drawPixmap(x, y, frameSpace[iter.current().terrainPatern][iter.current().terrainRotate]);
        else{
            fullMapPainter.translate(x+(CELL_SIZE / 2), y+(CELL_SIZE / 2));
            fullMapPainter.rotate(90*iter.current().terrainRotate);
            fullMapPainter.translate(-x-(CELL_SIZE / 2), -y-(CELL_SIZE / 2));
            fullMapPainter.drawPixmap(x, y, terrain[iter.current().terrain][iter.current().terrainPatern]);
            fullMapPainter.translate(x+(CELL_SIZE / 2), y+(CELL_SIZE / 2));
            fullMapPainter.rotate(90*(4-iter.current().terrainRotate));
            fullMapPainter.translate(-x-(CELL_SIZE / 2), -y-(CELL_SIZE / 2));
        }
        iter.nextDraw();
        x += CELL_SIZE;
        if (iter.getSize()*32 == x){
            y += CELL_SIZE;
            x = 0;
        }
    }
    x = 0;
    y = 0;
    iter.startDraw();
    while(!iter.isDoneDraw()){
        if(!iter.current().isFrame && iter.current().objectItem)
            fullMapPainter.drawPixmap(x+iter.current().objectItem->offset().x(), y+iter.current().objectItem->offset().y(), iter.current().objectItem->pixmap(iter.current().passability));
        iter.nextDraw();
        x += CELL_SIZE;
        if (iter.getSize()*32 == x){
            y += CELL_SIZE;
            x = 0;
        }
    }
    fullMapPainter.drawPixmap(colors[1].heroes->width*32-32, colors[1].heroes->height*32-32, QPixmap(":/objects/images/objects/ah00_03.png"));
    fullMapPainter.drawPixmap(enemies->curr_x1*32-32, enemies->curr_y1*32-32, QPixmap(":/objects/images/objects/ah12_03.png"));
    fullMapPainter.drawPixmap(enemies->curr_x2*32-32, enemies->curr_y2*32-32, QPixmap(":/objects/images/objects/ah12_03.png"));
    fullMapPainter.drawPixmap(enemies->curr_x3*32-32, enemies->curr_y3*32-32, QPixmap(":/objects/images/objects/ah12_03.png"));
    fullMapPainter.end();
    return fullMap;
}

void GameModel::keyPressChange(int x, int y){
    if(colors[1].heroes->width + x >= 9 && colors[1].heroes->width + x + 10 <= size && x != 0){
        if(originalField->getCell(colors[1].heroes->height + y, colors[1].heroes->width + x).passability == 0){
            if((colors[1].heroes->width + x == enemies->curr_x1 && colors[1].heroes->height + y == enemies->curr_y1) ||
                (colors[1].heroes->width + x == enemies->curr_x2 && colors[1].heroes->height + y == enemies->curr_y2) ||
                (colors[1].heroes->width + x == enemies->curr_x3 && colors[1].heroes->height + y == enemies->curr_y3)){
                *enemies+=colors[1].heroes;
                return;
            }
            QSound::play(":/technical/sounds/technical/HORSE00.wav");
            colors[1].heroes->width += x;
            logString = QString("Перемещение игрока на (").append(QString::number(colors[1].heroes->height)).append(", ").append(QString::number(colors[1].heroes->width)).append(")\n");
            notify();
            enemies->Move(originalField, QPoint(colors[1].heroes->width, colors[1].heroes->height));
            emit signalFieldChange(colors[1].heroes->width - 9, colors[1].heroes->height - 9);
            Snapshot* snap = new Snapshot(originalField, QPoint(colors[1].heroes->width, colors[1].heroes->height), QPoint(signalGetStartCam()), colors[1].gold,
                                          QPoint(enemies->curr_x1, enemies->curr_y1), QPoint(enemies->curr_x2, enemies->curr_y2), QPoint(enemies->curr_x3, enemies->curr_y3),
                                          isEnd);
            command->change(snap);
            return;
        }
        if(originalField->getCell(colors[1].heroes->height + y, colors[1].heroes->width + x).passability == 1){
            if((colors[1].heroes->width + x == enemies->curr_x1 && colors[1].heroes->height + y == enemies->curr_y1) ||
                (colors[1].heroes->width + x == enemies->curr_x2 && colors[1].heroes->height + y == enemies->curr_y2) ||
                (colors[1].heroes->width + x == enemies->curr_x3 && colors[1].heroes->height + y == enemies->curr_y3)){
                *enemies+=colors[1].heroes;
                return;
            }
            bool answer = originalField->getCell(colors[1].heroes->height + y, colors[1].heroes->width + x).objectItem->interactive(colors[1]);
            emit signalGoldChange(colors[1].gold);
            colors[1].heroes->width += x;
            logString = QString("Перемещение игрока на (").append(QString::number(colors[1].heroes->height)).append(", ").append(QString::number(colors[1].heroes->width)).append(")\n");
            notify();
            enemies->Move(originalField, QPoint(colors[1].heroes->width, colors[1].heroes->height));
            emit signalFieldChange(colors[1].heroes->width - 9, colors[1].heroes->height - 9);
            if(answer && !isEnd){
                emit signalEnd();
                isEnd = true;
            }
            Snapshot* snap = new Snapshot(originalField, QPoint(colors[1].heroes->width, colors[1].heroes->height), QPoint(signalGetStartCam()), colors[1].gold,
                                          QPoint(enemies->curr_x1, enemies->curr_y1), QPoint(enemies->curr_x2, enemies->curr_y2), QPoint(enemies->curr_x3, enemies->curr_y3),
                                          isEnd);
            command->change(snap);
        }
    }
    if(colors[1].heroes->height + y >= 9 && colors[1].heroes->height + y + 10 <= size && y != 0){
        if(originalField->getCell(colors[1].heroes->height + y, colors[1].heroes->width + x).passability == 0){
            if((colors[1].heroes->width + x == enemies->curr_x1 && colors[1].heroes->height + y == enemies->curr_y1) ||
                (colors[1].heroes->width + x == enemies->curr_x2 && colors[1].heroes->height + y == enemies->curr_y2) ||
                (colors[1].heroes->width + x == enemies->curr_x3 && colors[1].heroes->height + y == enemies->curr_y3)){
                *enemies+=colors[1].heroes;
                return;
            }
            QSound::play(":/technical/sounds/technical/HORSE00.wav");
            colors[1].heroes->height += y;
            logString = QString("Перемещение игрока на (").append(QString::number(colors[1].heroes->height)).append(", ").append(QString::number(colors[1].heroes->width)).append(")\n");
            notify();
            enemies->Move(originalField, QPoint(colors[1].heroes->width, colors[1].heroes->height));
            emit signalFieldChange(colors[1].heroes->width - 9, colors[1].heroes->height - 9);
            Snapshot* snap = new Snapshot(originalField, QPoint(colors[1].heroes->width, colors[1].heroes->height), QPoint(signalGetStartCam()), colors[1].gold,
                                          QPoint(enemies->curr_x1, enemies->curr_y1), QPoint(enemies->curr_x2, enemies->curr_y2), QPoint(enemies->curr_x3, enemies->curr_y3),
                                          isEnd);
            command->change(snap);
            return;
        }
        if(originalField->getCell(colors[1].heroes->height + y, colors[1].heroes->width + x).passability == 1){
            if((colors[1].heroes->width + x == enemies->curr_x1 && colors[1].heroes->height + y == enemies->curr_y1) ||
                (colors[1].heroes->width + x == enemies->curr_x2 && colors[1].heroes->height + y == enemies->curr_y2) ||
                (colors[1].heroes->width + x == enemies->curr_x3 && colors[1].heroes->height + y == enemies->curr_y3)){
                *enemies+=colors[1].heroes;
                return;
            }
            bool answer = originalField->getCell(colors[1].heroes->height + y, colors[1].heroes->width + x).objectItem->interactive(colors[1]);
            emit signalGoldChange(colors[1].gold);
            colors[1].heroes->height += y;
            logString = QString("Перемещение игрока на (").append(QString::number(colors[1].heroes->height)).append(", ").append(QString::number(colors[1].heroes->width)).append(")\n");
            notify();
            enemies->Move(originalField, QPoint(colors[1].heroes->width, colors[1].heroes->height));
            emit signalFieldChange(colors[1].heroes->width - 9, colors[1].heroes->height - 9);
            if(answer && !isEnd){
                emit signalEnd();
                logString = QString("Конец игры\n");
                notify();
                isEnd = true;
            }
            Snapshot* snap = new Snapshot(originalField, QPoint(colors[1].heroes->width, colors[1].heroes->height), QPoint(signalGetStartCam()), colors[1].gold,
                                          QPoint(enemies->curr_x1, enemies->curr_y1), QPoint(enemies->curr_x2, enemies->curr_y2), QPoint(enemies->curr_x3, enemies->curr_y3),
                                          isEnd);
            command->change(snap);
        }
    }
}

QString GameModel::writeLog() const{
    return logString;
}

void GameModel::Save(QString path){
    emit signalSaveProcess();
    command->saveCommand(path);
    emit signalEndSave();
}
