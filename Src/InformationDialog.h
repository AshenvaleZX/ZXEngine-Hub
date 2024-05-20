#include <QDialog>
#include <QtWidgets>

class InformationDialog : public QDialog
{
    Q_OBJECT

public:
    InformationDialog(QWidget* parent = nullptr);
    ~InformationDialog() {};

public slots:
    void OnSetPathClicked();
};
