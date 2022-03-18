#ifndef RESOURCEBAR_H
#define RESOURCEBAR_H
#include <QLabel>

class ResourceBar
{
public:
    ResourceBar();
    ~ResourceBar();
    QLabel* tree;
    QLabel* mercury;
    QLabel* ore;
    QLabel* sulfur;
    QLabel* crystal;
    QLabel* gem;
    QLabel* gold;
};

#endif // RESOURCEBAR_H
