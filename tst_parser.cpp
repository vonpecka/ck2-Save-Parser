#include <QtTest>
#include <ck2Parser.h>

class Parser : public QObject
{
    Q_OBJECT

public:
    Parser();
    ~Parser();

private slots:
    void test_characterName();
    void test_structAttributes();
    void test_characterAttributes();
    void test_characterSpouse();

};

Parser::Parser()
{

}

Parser::~Parser()
{

}

void Parser::test_characterName()
{
    ck2::File file("Derby775_07_18.ck2");
    ck2::SaveFile save(file);
    ck2::Character player = save.getCharacter(504285);
    QCOMPARE(player.name(),std::string("Harthgate"));
}

void Parser::test_structAttributes()
{
    ck2::Attributes attrib("2 6 9 5 8");
    QCOMPARE(int(attrib.diplomacy()), 2);
    QCOMPARE(int(attrib.marshall()), 6);
    QCOMPARE(int(attrib.stewardship()), 9);
    QCOMPARE(int(attrib.intrigue()), 5);
    QCOMPARE(int(attrib.learning()), 8);
}

void Parser::test_characterAttributes()
{
    ck2::File file("Derby775_07_18.ck2");
    ck2::SaveFile save(file);
    ck2::Character player = save.getCharacter(502726);
    ck2::Attributes attrib("2 1 1 7 4");
    QCOMPARE(attrib.diplomacy(), player.attributes().diplomacy());
    QCOMPARE(attrib.marshall(), player.attributes().marshall());
    QCOMPARE(attrib.stewardship(), player.attributes().stewardship());
    QCOMPARE(attrib.intrigue(), player.attributes().intrigue());
    QCOMPARE(attrib.learning(), player.attributes().learning());
}

void Parser::test_characterSpouse()
{
    ck2::File file("Derby775_07_18.ck2");
    ck2::SaveFile save(file);
    ck2::Character player = save.getCharacter(504306);
    ck2::Character player2 = save.getCharacter(190329);
    QCOMPARE(player.spouse()->name(), player2.name());
}
QTEST_APPLESS_MAIN(Parser)

#include "tst_parser.moc"
