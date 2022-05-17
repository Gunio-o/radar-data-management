#ifndef DIRTREE_H
#define DIRTREE_H
#include <QObject>
#include <QWidget>
#include <QApplication>
#include <QFileSystemModel>
#include <QFileIconProvider>
#include <QScreen>
#include <QTreeWidget>
#include <QTreeView>
#include <QCommandLineParser>
#include <QCommandLineOption>


class DirTree : public QTreeView
{
    Q_OBJECT
public:
    DirTree(QWidget *parent = nullptr);
    void setPath(QString path);
private:
    QFileSystemModel *model;
};

#endif // DIRTREE_H
