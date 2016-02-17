//-----------------------------------------------------------------------------------------------------------------------------
// think-cell public library
// Copyright (C) 2016 think-cell Software GmbH
//
// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as 
// published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. 
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty 
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. 
//
// You should have received a copy of the GNU General Public License along with this program. 
// If not, see <http://www.gnu.org/licenses/>. 
//-----------------------------------------------------------------------------------------------------------------------------

#include "range.h"
#include "range.t.h"

namespace {
	void static_tests() noexcept {
		auto rngSize = tc::transform(tc::vector<int>(), [](int) { return 0; });
		static_assert(tc::size_impl::has_size<decltype(rngSize)>::value, "");

		auto rngNoSize = tc::transform(tc::filter(tc::vector<int>(), [](int){ return false; }), [](int) { return 0; });
		static_assert(!tc::size_impl::has_size<decltype(rngNoSize)>::value, "");
	}
}

UNITTESTDEF(vector_int_ref_need_sfinae_transform) {
	tc::vector<int> vecn{1,2,3};
	auto rgntrnsfn = tc::transform(vecn, [](int& n) {return n*n;});
	auto it = boost::begin(rgntrnsfn);
	_ASSERTEQUAL(*it++,1);
	_ASSERTEQUAL(*it++,4);
	_ASSERTEQUAL(*it++,9);
}