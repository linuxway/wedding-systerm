#include <QtTest/QtTest>

#include"systemManager.h"
#include"productType.h"
#include"productCatalog.h"
#include"productDescription.h"

Q_DECLARE_METATYPE(QList<QStringList>);
class TestWedding:public QObject
{
Q_OBJECT
private slots:
    void initTestCase();
    void cleanupTestCase();

    void MakeNewCatalog();

    void EnterFirstLevelTypes();
    void EnterFirstLevelTypes_data();

    void EnterSecondLevelTypes();
    void EnterSecondLevelTypes_data();

    void EmptySecondLevelTypes();

    void EnterProductDescriptionForType();

private:
    SystemManager *_sys;
};


void TestWedding::initTestCase()
{
    _sys = new SystemManager();
}

void TestWedding::cleanupTestCase()
{
    delete _sys;
}

void TestWedding::MakeNewCatalog()
{
    _sys->MakeNewCatalog();
    ProductCatalog *catalog = _sys->Catalog();
    QVERIFY(catalog!=NULL);

    QList<ProductType *> list = catalog->FirstLevelTypes();
    QVERIFY(list.size()==0);
}


void TestWedding::EnterFirstLevelTypes_data()
{
    QTest::addColumn<QStringList>("firstTypes");

    QStringList data;
    data << tr("���ز���")
         << tr("רҵ����")
         << tr("�鳵����")
         << tr("�ʻ�����")
         << tr("��Ӱ����")
         << tr("���ﻯױ");

    QTest::newRow("ϲ��ͨһ������") << data;
}

void TestWedding::EnterFirstLevelTypes()
{
    QFETCH(QStringList,firstTypes);

    _sys->MakeNewCatalog();
    _sys->EnterFirstLevelTypes(firstTypes);
    ProductCatalog *catalog = _sys->Catalog();
    QList<ProductType *> list = catalog->FirstLevelTypes();
    QCOMPARE(list.size(),firstTypes.size());

    for(int i = 0; i < list.size(); ++i) {
        QCOMPARE(list[i]->Name(), firstTypes[i]);
    }
}

void TestWedding::EnterSecondLevelTypes_data()
{
    QTest::addColumn<QStringList>("firstTypeList");
    QTest::addColumn<QList<QStringList> >("secondTypeLL");

    // 1. test full first/second level catalog
    QString firstType = tr("���ز���");
    QStringList secondTypeList;
    secondTypeList << tr("�ʻ�����")
                   << tr("������")
                   << tr("�ƹ�����")
                   << tr("�����豸");

    QString firstType1 = tr("רҵ����");
    QStringList secondTypeList1;
    secondTypeList1 << tr("��ϯ����")
                    << tr("��������");

    QString firstType2 = tr("�鳵����");
    QStringList secondTypeList2;
    secondTypeList2 << tr("����ͷ��")
                    << tr("�鳵����");

    QString firstType3 = tr("�ʻ�װ��");
    QStringList secondTypeList3;
    secondTypeList3 << tr("�����ʻ�ϵ��")
                    << tr("�鳵�û�");

    QStringList firstTypeList = QStringList() << firstType
                                              << firstType1
                                              << firstType2
                                              << firstType3;

    QList<QStringList> secondTypeLL;
    secondTypeLL << secondTypeList
                 << secondTypeList1
                 << secondTypeList2
                 << secondTypeList3;

    QTest::newRow("ϲ��ͨĿ¼") << firstTypeList << secondTypeLL;
}

void TestWedding::EnterSecondLevelTypes()
{
    QFETCH(QStringList ,firstTypeList);
    QFETCH(QList<QStringList> ,secondTypeLL);

    _sys->MakeNewCatalog();
    _sys->EnterFirstLevelTypes(firstTypeList);

    for (int i = 0; i < firstTypeList.size(); ++i) {
        _sys->EnterSecondLevelTypes(firstTypeList[i], secondTypeLL[i]);
    }

    ProductCatalog *catalog = _sys->Catalog();
    for (int firstIndex = 0; firstIndex < firstTypeList.size(); ++firstIndex) {
        QList<ProductType *> secondTypes = catalog->SecondLevelTypes(firstTypeList[firstIndex]);
        QVERIFY(secondTypes.size() == secondTypeLL[firstIndex].size());

        for (int secondIndex = 0; secondIndex < secondTypes.size(); ++secondIndex) {
            QCOMPARE(secondTypes[secondIndex]->Name(), secondTypeLL[firstIndex][secondIndex]);
        }
    }
}

void TestWedding::EmptySecondLevelTypes()
{
    QString firstType = tr("���ز���");
    QString firstType1 = tr("רҵ����");
    QString firstType2 = tr("�鳵����");
    QString firstType3 = tr("�ʻ�װ��");
    QStringList firstTypeList = QStringList() << firstType
                                              << firstType1
                                              << firstType2
                                              << firstType3;

    _sys->MakeNewCatalog();
    _sys->EnterFirstLevelTypes(firstTypeList);


    QStringList secondTypeList;
    secondTypeList << tr("�ʻ�����")
                   << tr("������")
                   << tr("�ƹ�����")
                   << tr("�����豸");
    _sys->EnterSecondLevelTypes(firstType, secondTypeList);


    QStringList secondTypeList2;
    secondTypeList2 << tr("����ͷ��")
                    << tr("�鳵����");
    _sys->EnterSecondLevelTypes(firstType2, secondTypeList2);

    ProductCatalog *catalog = _sys->Catalog();

    QVERIFY(catalog->FirstLevelTypes().size() == 4);

    QList<ProductType *> secondTypes = catalog->SecondLevelTypes(firstType);
    QVERIFY(secondTypes.size() == 4);

    secondTypes = catalog->SecondLevelTypes(firstType1);
    QVERIFY(secondTypes.size() == 0);

    secondTypes = catalog->SecondLevelTypes(firstType2);
    QVERIFY(secondTypes.size() == 2);

    secondTypes = catalog->SecondLevelTypes(firstType3);
    QVERIFY(secondTypes.size() == 0);
}

void TestWedding::EnterProductDescriptionForType()
{
    QString firstType = tr("���ز���");
    QStringList firstTypeList = QStringList() << firstType;
    _sys->MakeNewCatalog();
    _sys->EnterFirstLevelTypes(firstTypeList);

    QStringList secondTypeList;
    secondTypeList << tr("�ʻ�����")
                   << tr("������")
                   << tr("�ƹ�����")
                   << tr("�����豸");
    _sys->EnterSecondLevelTypes(firstType, secondTypeList);

    ProductDescription *pd = new ProductDescription();
    pd->SetPath("/home/source/");
    pd->SetText(tr("���Ǻ�ɫõ�廨"));
    pd->SetPrice("5RMB");
    pd->SetFormat(tr("ͼƬ"));
    _sys->EnterProductDescriptionForType(tr("�ʻ�����"),pd);

    ProductCatalog *catalog = _sys->Catalog();
    QList<ProductDescription *> dList = catalog->DescriptionsFor(tr("�ʻ�����"));
    QVERIFY(dList.size() == 1);
    QCOMPARE(dList[0]->Path(), pd->Path());
    QCOMPARE(dList[0]->Text(), pd->Text());
    QCOMPARE(dList[0]->Price(), pd->Price());
    QCOMPARE(dList[0]->Format(), pd->Format());
}

QTEST_MAIN(TestWedding)
#include"test.moc"
