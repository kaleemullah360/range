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

#pragma once

#include "noncopyable.h"
#include "has_mem_fn.h"
#include "remove_cvref.h"

#define tc_in_place(expr) \
	(expr)=(expr)

TC_HAS_MEM_FN_XXX_TRAIT_DEF( negate )
TC_HAS_MEM_FN_XXX_TRAIT_DEF( bitwise_not )

namespace tc {
	namespace in_place_adl_barrier {
		template< typename T >
		std::enable_if_t< has_mem_fn_negate<T>::value > negate(T& t) noexcept {
			t.negate();
		}
		template< typename T >
		std::enable_if_t< !has_mem_fn_negate<T>::value > negate(T& t) noexcept {
			t=-t;
		}
		template< typename T >
		std::enable_if_t< has_mem_fn_bitwise_not<T>::value > bitwise_not(T& t) noexcept {
			t.bitwise_not();
		}
		template< typename T >
		std::enable_if_t< !has_mem_fn_bitwise_not<T>::value > bitwise_not(T& t) noexcept {
			t = ~t;
		}
		template< typename T >
		struct in_place final : tc::noncopyable {
			in_place(T& t) noexcept:m_t(t){}
			in_place const& operator-() const noexcept {
				negate(m_t); // allow ADL
				return *this;
			}
			in_place const& operator~() const noexcept {
				bitwise_not(m_t); // allow ADL
				return *this;
			}
			in_place const& operator!() const noexcept {
				m_t=!m_t;
				return *this;
			}
		private:
			T& m_t;
		};
	};
	template< typename T >
	in_place_adl_barrier::in_place<T> in_place(T& t) noexcept{
		return in_place_adl_barrier::in_place<T>(t);
	}
}