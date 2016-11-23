#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>

#include <rapidcheck.h>

enum class Department {
	Engineering,
	HumanResources,
	Sales,
};

struct Employee {
	std::string name;
	Department department;
	std::chrono::system_clock::time_point dob;
};


// NOTE: Must be in rc namespace!
namespace rc {

template<>
struct Arbitrary<Department> {
  static Gen<Department> arbitrary() {
    return gen::map(gen::inRange(0,2),[](int i) {
			switch(i) {
					case 0: return Department::Engineering;
					case 1: return Department::HumanResources;
					case 2: return Department::Sales;
					default: assert(false);
				}
		});
	}
};

template<>
struct Arbitrary<Employee> {
	using tp = std::chrono::system_clock::time_point;
	using years = typename std::chrono::duration<long long,std::ratio<31557600>>;

  static Gen<Employee> arbitrary() {
    return gen::build<Employee>(
        gen::set(&Employee::name),
        gen::set(&Employee::department),
        gen::set(&Employee::dob, gen::map(gen::inRange(18,80),[](int i) {
					return tp(years(-i));
				})));
    }
};

}

std::vector<int> reverse(std::vector<int> const& in) {
	std::vector<int> vec(in);
	for(size_t i = 0; i < vec.size() / 2; ++i) {
		std::swap(vec[i],vec[(i + vec.size() - 1) % vec.size()]);
	}
	return vec;
}

void sort_by_age(std::vector<Employee>& in) {
	std::sort(in.begin(),in.end(),
						[](Employee const& a,Employee const& b) {
							return a.dob > b.dob;
						});
}

int main() {
	rc::check("sort by age",
						[](std::vector<Employee> const& l0) {
							auto l1 = l0;
							sort_by_age(l1);
							RC_ASSERT(l0.size() == l1.size());
						});

	rc::check("double reversal yields the original value",
						[](std::vector<int> const& l0) {
							std::vector<int> l1 = reverse(reverse(l0));
							RC_ASSERT(l0 == l1);
						});
	return 0;
}
