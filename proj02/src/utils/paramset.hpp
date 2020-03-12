#ifndef PARAMSET_HPP
#define PARAMSET_HPP

#include <memory>
#include <string>
#include <unordered_map>

using std::make_shared;
using std::move;
using std::shared_ptr;
using std::static_pointer_cast;
using std::string;
using std::unique_ptr;
using std::unordered_map;

template<class T>
struct ParamSetItem{
	const unique_ptr< T[]> values;
	const size_t size;
	bool used;

	ParamSetItem (unique_ptr< T[]> v, size_t sz=1, bool u=false) : values(move(v)), size(sz), used(u){}
};

class ParamSet{

private:
	unordered_map< string, shared_ptr< void > > params;

public:
	template<typename T>
	void add (const string &new_key, unique_ptr< T[]> values, size_t size=1){
		shared_ptr<ParamSetItem<T>> item = make_shared<ParamSetItem<T>>(move(values), size, false);
		params[new_key] = item;
	}

	// TODO
	template<typename T>
	bool erase (const string &target_key);
	
	template<typename T>
	const T & find_one (const string &target_key, const T &d) const{
		try {
			auto psi = static_pointer_cast<ParamSetItem<T>>(params.at(target_key));
			return psi->values[0];
		}
		  catch (const std::out_of_range& oor) {
		    return d;
		}

		return d;
	}

	template<typename T>
	const T* find_array (const string &target_key, size_t &size) const{
		T* retVal = nullptr;

		try {
			auto psi = static_pointer_cast<ParamSetItem<T>>(params.at(target_key));
			size = psi->size;
			retVal = psi->values.get();
		}
		  catch (const std::out_of_range& oor) {
		    retVal = nullptr;
		}

		return retVal;
	}
};

#endif