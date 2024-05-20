#include <QMainWindow>
#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() {};

    void SetEnginePath(const QString& path);

private:
    QString mEnginePath;
    QSettings mSettings;
    QStringList mProjects;
    QListWidget* mProjectList;

    void AddProject();
    void RemoveProject();
    void UpdateProjectList();
    void PopInfo();
};
