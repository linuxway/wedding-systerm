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

    void FinishEnterCatalog();

private:
    void _CompareSecondLevel(ProductCatalog *,
                             const QStringList &,
                             const QList<QStringList> &);
    void _CompareFirstLevel(const QList<ProductType *> &, const QStringList &);
    void _CompareDescription(ProductDescription *, ProductDescription *);

    SystemManager *_sys;
};


void TestWedding::initTestCase()
{
    DBFacade *db = new MockDBFacade();
    _sys = new SystemManager(db);
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
    _CompareFirstLevel(catalog->FirstLevelTypes(), firstTypes);
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
    _CompareSecondLevel(catalog, firstTypeList, secondTypeLL);
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
    pd->SetPrice(5);
    pd->SetFormat(ProductDescription::FORMAT_PICTURE);
    _sys->EnterProductDescriptionForType(tr("�ʻ�����"),pd);

    ProductCatalog *catalog = _sys->Catalog();
    QList<ProductDescription *> dList = catalog->DescriptionsFor(tr("�ʻ�����"));
    QVERIFY(dList.size() == 1);
    _CompareDescription(dList[0], pd);
}

void TestWedding::_CompareDescription(ProductDescription *description,
                                      ProductDescription *golden)
{
    QCOMPARE(description->Path(), golden->Path());
    QCOMPARE(description->Text(), golden->Text());
    QCOMPARE(description->Price(), golden->Price());
    QCOMPARE(description->Format(), golden->Format());
}

void TestWedding::FinishEnterCatalog()
{
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

    ProductDescription *rose = new ProductDescription();
    rose->SetPath("/home/source/");
    rose->SetText(tr("���Ǻ�ɫõ�廨"));
    rose->SetPrice(100);
    rose->SetFormat(ProductDescription::FORMAT_PICTURE);

    ProductDescription *lily = new ProductDescription();
    lily->SetPath("/home/source/");
    lily->SetText(tr("�ٺϻ�"));
    lily->SetPrice(100);
    lily->SetFormat(ProductDescription::FORMAT_PICTURE);

    ProductDescription *bmw = new ProductDescription();
    bmw->SetPath("/home/source/");
    bmw->SetText(tr("����750"));
    bmw->SetPrice(1000);
    bmw->SetFormat(ProductDescription::FORMAT_PICTURE);

    ProductDescription *bubble = new ProductDescription();
    bubble->SetPath("/home/source/");
    bubble->SetText(tr("���ݻ�"));
    bubble->SetPrice(50);
    bubble->SetFormat(ProductDescription::FORMAT_PICTURE);

    ProductDescription *mrHan = new ProductDescription();
    mrHan->SetPath("/home/source/");
    mrHan->SetText(tr("������"));
    mrHan->SetPrice(1000);
    mrHan->SetFormat(ProductDescription::FORMAT_PICTURE);

    _sys->MakeNewCatalog();
    _sys->EnterFirstLevelTypes(firstTypeList);
    _sys->EnterSecondLevelTypes(firstType1, secondTypeList1);
    _sys->EnterSecondLevelTypes(firstType2, secondTypeList2);
    _sys->EnterSecondLevelTypes(firstType3, secondTypeList3);
    _sys->EnterProductDescriptionForType(tr("�ʻ�����"), rose);
    _sys->EnterProductDescriptionForType(tr("�鳵�û�"), lily);
    _sys->EnterProductDescriptionForType(tr("����ͷ��"), bmw);
    _sys->EnterProductDescriptionForType(tr("��ϯ����"), mrHan);
    _sys->EnterProductDescriptionForType(tr("�����豸"), bubble);
    _sys->FinishEnterCatalog();

    DBFacade *db = _sys->DBFacade();
    ProductCatalog *catalog = db->Catalog();

    _CompareFirstLevel(catalog->FirstLevelTypes(), firstTypeList);
    _CompareSecondLevel(catalog, firstTypeList, secondTypeLL);

    QList<ProductDescription *> dList = catalog->DescriptionsFor(tr("�ʻ�����"));
    QVERIFY(dList.size() == 1);
    _CompareDescription(dList[0], rose);

    dList = catalog->DescriptionsFor(tr("�鳵�û�"));
    QVERIFY(dList.size() == 1);
    _CompareDescription(dList[0], lily);

    dList = catalog->DescriptionsFor(tr("����ͷ��"));
    QVERIFY(dList.size() == 1);
    _CompareDescription(dList[0], bmw);

    dList = catalog->DescriptionsFor(tr("��ϯ����"));
    QVERIFY(dList.size() == 1);
    _CompareDescription(dList[0], mrHan);

    dList = catalog->DescriptionsFor(tr("�����豸"));
    QVERIFY(dList.size() == 1);
    _CompareDescription(dList[0], bubble);
}

void TestWedding::_CompareFirstLevel(const QList<ProductType *> &list,
                                     const QStringList &golden)
{
    QCOMPARE(list.size(),golden.size());

    for(int i = 0; i < list.size(); ++i) {
        QCOMPARE(list[i]->Name(), golden[i]);
    }
}

void TestWedding::_CompareSecondLevel(ProductCatalog *catalog,
                                      const QStringList &firstLevel,
                                      const QList<QStringList> &secondLevelGolden)
{
    for (int firstIndex = 0; firstIndex < firstLevel.size(); ++firstIndex) {
        QList<ProductType *> secondTypes =
                catalog->SecondLevelTypes(firstLevel[firstIndex]);
        QVERIFY(secondTypes.size() == secondLevelGolden[firstIndex].size());

        for (int secondIndex = 0; secondIndex < secondTypes.size(); ++secondIndex) {
            QCOMPARE(secondTypes[secondIndex]->Name(),
                     secondLevelGolden[firstIndex][secondIndex]);
        }
    }
}

QTEST_MAIN(TestWedding)
#include"test.moc"
