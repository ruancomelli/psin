#define BOOST_TEST_MODULE JSONLibTest

#include <fstream>
#include <iostream>
#include <string>

// JSONLib
#include <json.hpp>

// UtilsLib
#include <Test.hpp>

using namespace psin;
using std::ifstream;
using std::ofstream;
using std::string;

TestCase(basic_json_Test)
{
	string filename = "file.json";

	json j = {
		{"pi", 3.141},
		{"happy", true},
		{"name", "Niels"},
		{"nothing", nullptr},
		{"answer", {
			{"everything", 42}
		}},
		{"list", {1, 0, 2}},
		{"object", {
			{"currency", "USD"},
			{"value", 42.99}
		}}
	};

	auto happy_value = j["happy"];
	auto list_value = j["list"];

	checkEqual(j["pi"], 3.141);
	checkEqual(happy_value, true);
	checkEqual(list_value[1], 0);

	ofstream out(filename);
	out << j.dump(4);
	out.close();

	ifstream in(filename);
	json j2;
	in >> j2;

	checkEqual(j2["name"], "Niels");
	checkEqual(j2["answer"]["everything"], 42);

	json obj = j2["object"];

	checkEqual(obj["currency"], "USD");
	checkEqual(obj["value"], 42.99);	
}

namespace to_and_from_json_Test_namespace {

	struct A
	{
		void set(const int x){ this->x = x; }
		int get() const { return this->x; }
		double z;
		string name;

	private:
		int x;
	};

    void to_json(json& j, const A& a) {
        j = json{{"name", a.name}, {"x", a.get()}, {"z", a.z}};
    }

    void from_json(const json& j, A& a) {
        a.name = j.at("name").get<std::string>();
        a.set( j.at("x").get<int>() );
        a.z = j.at("z").get<double>();
    }

} // to_and_from_json_Test_namespace

TestCase(to_and_from_json_Test)
{
	using namespace to_and_from_json_Test_namespace;

	A a1;
	A a2;
	json j;

	a1.name = "a1";
	a1.z = 3.14;
	a1.set(10);

	j = a1;

	a2 = j;

	checkEqual(a2.name, "a1");
	checkEqual(a2.z, 3.14);
	checkEqual(a2.get(), 10);
}