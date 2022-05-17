#include "dirtree.h"


DirTree::DirTree(QWidget *parent) : QTreeView(parent)
{
    model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    model->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

    setModel(model);
    setRootIndex(model->index(QDir::currentPath()));


}


void DirTree::setPath(QString path)
{
    model->setRootPath(path);
    setRootIndex(model->index(model->rootPath()));
}
