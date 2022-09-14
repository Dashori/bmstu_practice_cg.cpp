class TestTriangle : public QObject
{
    Q_OBJECT

    public:
        explicit TestTriangle(QObject *parent = nullptr);

    private slots:
        void test_findZ();
};