#include <QtTest>
#include <parseddata.h>

class ParserTest : public QObject
{
    Q_OBJECT

public:
    ParserTest();
    ~ParserTest();

private slots:
    void test_characterName();
    void test_structAttributes();
    void test_characterAttributes();
    void test_characterSpouse();
    void test_landedTitle();
    void test_landedTitleLiege();
    void test_landedTitleSuccesion();
    void test_landedTitleGender();
};

ParserTest::ParserTest()
{

}

ParserTest::~ParserTest()
{

}

void ParserTest::test_characterName()
{
    ck2::DataFile file("Derby775_07_18.ck2");
    ck2::ParsedData save(file);
    ck2::Character player = save.getCharacter(504285);
    QCOMPARE(player.name(),std::string("Harthgate"));
}

void ParserTest::test_structAttributes()
{
    ck2::Attributes attrib("2 6 9 5 8");
    QCOMPARE(int(attrib.diplomacy()), 2);
    QCOMPARE(int(attrib.marshall()), 6);
    QCOMPARE(int(attrib.stewardship()), 9);
    QCOMPARE(int(attrib.intrigue()), 5);
    QCOMPARE(int(attrib.learning()), 8);
}

void ParserTest::test_characterAttributes()
{
    ck2::DataFile file("Derby775_07_18.ck2");
    ck2::ParsedData save(file);
    ck2::Character player = save.getCharacter(502726);
    ck2::Attributes attrib("2 1 1 7 4");
    QCOMPARE(attrib.diplomacy(), player.attributes().diplomacy());
    QCOMPARE(attrib.marshall(), player.attributes().marshall());
    QCOMPARE(attrib.stewardship(), player.attributes().stewardship());
    QCOMPARE(attrib.intrigue(), player.attributes().intrigue());
    QCOMPARE(attrib.learning(), player.attributes().learning());
}

void ParserTest::test_characterSpouse()
{
    ck2::DataFile file("Derby775_07_18.ck2");
    ck2::ParsedData save(file);
    ck2::Character player = save.getCharacter(504306);
    ck2::Character player2 = save.getCharacter(190329);
    QCOMPARE(player.spouse()->name(), player2.name());
}

void ParserTest::test_landedTitle()
{
    ck2::DataFile file("Derby775_07_18.ck2");
    ck2::ParsedData save(file);
    ck2::Title title = save.getLandedTitle("d_gelre");
    QCOMPARE(int(title.holderID()), 6392);
}

void ParserTest::test_landedTitleLiege()
{
    ck2::DataFile file("Derby775_07_18.ck2");
    ck2::ParsedData save(file);
    ck2::Title title = save.getLandedTitle("d_gelre");
    QCOMPARE(title.liege(), std::string("k_france"));
}

void ParserTest::test_landedTitleSuccesion()
{
    ck2::DataFile file("Derby775_07_18.ck2");
    ck2::ParsedData save(file);
    ck2::Title title = save.getLandedTitle("d_gelre");
    QCOMPARE(title.succession(), std::string("gavelkind"));
}

void ParserTest::test_landedTitleGender()
{
    ck2::DataFile file("Derby775_07_18.ck2");
    ck2::ParsedData save(file);
    ck2::Title title = save.getLandedTitle("d_gelre");
    QCOMPARE(title.gender(), std::string("agnatic"));
}


QTEST_APPLESS_MAIN(ParserTest)

#include "tst_parser.moc"
