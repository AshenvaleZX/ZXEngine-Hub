#include "InformationDialog.h"
#include "MainWindow.h"

InformationDialog::InformationDialog(QWidget* parent) : QDialog(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* label = new QLabel(
        "ZXEngine:<br>"
        "<a href=\"https://github.com/AshenvaleZX/ZXEngine\">https://github.com/AshenvaleZX/ZXEngine</a><br><br>"
        "ZXEngine Hub:<br>"
        "<a href=\"https://github.com/AshenvaleZX/ZXEngine-Hub\">https://github.com/AshenvaleZX/ZXEngine-Hub</a><br><br>"
        "ZXEngine Demo Projects:<br>"
        "<a href=\"https://github.com/AshenvaleZX/ZXEngine-Demo-Projects\">https://github.com/AshenvaleZX/ZXEngine-Demo-Projects</a><br>", this
    );
    
    label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    label->setOpenExternalLinks(true);
    layout->addWidget(label, 0, Qt::AlignCenter);

    QPushButton* button = new QPushButton(" Set Engine Path ", this);
    connect(button, &QPushButton::clicked, this, &InformationDialog::OnSetPathClicked);
    layout->addWidget(button, 0, Qt::AlignCenter);

    this->resize(450, 200);
}

void InformationDialog::OnSetPathClicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Select Engine"), "", "All Files (*)");

    if (path.isEmpty())
        return;

    MainWindow* mainWindow = qobject_cast<MainWindow*>(parent());
    if (mainWindow)
    {
        mainWindow->SetEnginePath(path);
    }

    this->close();
}
