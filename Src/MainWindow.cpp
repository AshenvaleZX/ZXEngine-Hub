#include "MainWindow.h"
#include "InformationDialog.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    mSettings("AshenvaleZX", "ZXEngine Hub")
{
    QFont boldFont;
    boldFont.setBold(true);

    auto btnAbout = new QPushButton("About", this);
    btnAbout->setGeometry(135, 300, 80, 30);
    btnAbout->setFont(boldFont);
    connect(btnAbout, &QPushButton::clicked, this, &MainWindow::PopInfo);

    auto btnAdd = new QPushButton("Add", this);
    btnAdd->setGeometry(420, 345, 100, 40);
    btnAdd->setFont(boldFont);
    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::AddProject);

    auto btnRemove = new QPushButton("Remove", this);
    btnRemove->setGeometry(580, 345, 100, 40);
    btnRemove->setFont(boldFont);
    connect(btnRemove, &QPushButton::clicked, this, &MainWindow::RemoveProject);

    // Icon
    QIcon appIcon(":/Images/icon.png");
    this->setWindowIcon(appIcon);

    QPixmap pixmap(":/Images/logo.png");
    QLabel* label = new QLabel(this);
    label->setGeometry(50, 50, 250, 250);
    pixmap = pixmap.scaled(label->width(), label->height(), Qt::KeepAspectRatio);
    label->setPixmap(pixmap);

    // Load the engine path and projects from the settings
    mEnginePath = mSettings.value("EnginePath").toString();
    mProjects = mSettings.value("Projects").toStringList();
    statusBar()->showMessage(mEnginePath);

    // Projects List
    mProjectList = new QListWidget(this);
    mProjectList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    mProjectList->setGeometry(350, 30, 400, 300);
    UpdateProjectList();

    connect(mProjectList, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem* item){
        QString path = item->data(Qt::UserRole).toString();

        QProcess* process = new QProcess(this);
        process->start(mEnginePath, QStringList() << path);

        // Move the item to the top of the list
        int row = mProjectList->row(item);
        if (row > 0)
        {
            mProjects.move(row, 0);
            UpdateProjectList();
            mSettings.setValue("Projects", mProjects);
        }
    });

    this->resize(800, 400);
}

void MainWindow::SetEnginePath(const QString& path)
{
    mEnginePath = path;
    statusBar()->showMessage(path);
    mSettings.setValue("EnginePath", path);
}

void MainWindow::AddProject()
{
    QString dirPath = QFileDialog::getExistingDirectory(this, 
        tr("Add Project"), "", 
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );

    if (dirPath.isEmpty())
        return;

    for (int i = 0; i < mProjects.size(); ++i)
    {
        if (mProjects[i] == dirPath)
        {
            mProjects.removeAt(i);
            break;
        }
    }

    mProjects.prepend(dirPath);

    UpdateProjectList();

    mSettings.setValue("Projects", mProjects);
}

void MainWindow::RemoveProject()
{
    QListWidgetItem* item = mProjectList->currentItem();
    if (item == nullptr)
        return;

    QString path = item->data(Qt::UserRole).toString();

    for (int i = 0; i < mProjects.size(); ++i)
    {
        if (mProjects[i] == path)
        {
            mProjects.removeAt(i);
            break;
        }
    }

    UpdateProjectList();

    mSettings.setValue("Projects", mProjects);
}

void MainWindow::UpdateProjectList()
{
    mProjectList->clear();
    for (const auto& path : mProjects)
    {
        // Create an outer widget with a layout
        QWidget* outerWidget = new QWidget();
        QVBoxLayout* outerLayout = new QVBoxLayout();
        // Border radius
        outerLayout->setContentsMargins(5, 5, 5, 5);
        outerWidget->setLayout(outerLayout);

        // Create an inner widget with two labels
        QWidget* innerWidget = new QWidget();
        QVBoxLayout* innerLayout = new QVBoxLayout();

        QDir dir(path);
        QString name = dir.dirName();

        QLabel* label1 = new QLabel(name);
        QLabel* label2 = new QLabel(path);

        label1->setStyleSheet("font-weight: bold; font-size: 18px;");
        label2->setStyleSheet("font-size: 12px;");

        innerLayout->addWidget(label1);
        innerLayout->addWidget(label2);
        innerWidget->setLayout(innerLayout);

        // Set the background color and border radius of the inner widget
        innerWidget->setStyleSheet("background-color: rgb(235, 235, 255); border-radius: 10px;");

        // Add the inner widget to the outer layout
        outerLayout->addWidget(innerWidget);

        // Create a QListWidgetItem and set the outer widget as its widget
        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(outerWidget->sizeHint());
        item->setData(Qt::UserRole, path);
        mProjectList->addItem(item);
        mProjectList->setItemWidget(item, outerWidget);
    }
}

void MainWindow::PopInfo()
{
    InformationDialog dialog(this);
    dialog.exec();
}
