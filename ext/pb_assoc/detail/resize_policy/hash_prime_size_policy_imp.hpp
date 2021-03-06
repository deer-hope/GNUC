// -*- C++ -*-

// Copyright (C) 2005 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
// USA.

// As a special exception, you may use this file as part of a free software
// library without restriction.  Specifically, if other files instantiate
// templates or use macros or inline functions from this file, or you compile
// this file and link it with other files to produce an executable, this
// file does not by itself cause the resulting executable to be covered by
// the GNU General Public License.  This exception does not however
// invalidate any other reasons why the executable file might be covered by
// the GNU General Public License.

// Copyright (C) 2004 Ami Tavory and Vladimir Dreizin, IBM-HRL.

// Permission to use, copy, modify, sell, and distribute this software
// is hereby granted without fee, provided that the above copyright
// notice appears in all copies, and that both that copyright notice and
// this permission notice appear in supporting documentation. None of
// the above authors, nor IBM Haifa Research Laboratories, make any
// representation about the suitability of this software for any
// purpose. It is provided "as is" without express or implied warranty.

/*
 * @file hash_prime_size_policy_imp.hpp
 * Contains an implementation of hash_prime_size_policy.
 */

namespace detail
{

  enum
    {
      num_distinct_sizes = 28
    };

  static const size_t s_a_sizes[num_distinct_sizes] =
    {
      /* Dealing cards... */
      /* 0	*/ 53ul,
      /* 1	*/ 97ul,
      /* 2	*/ 193ul,
      /* 3	*/ 389ul,
      /* 4	*/ 769ul,
      /* 5	*/ 1543ul,
      /* 6	*/ 3079ul,
      /* 7	*/ 6151ul,
      /* 8	*/ 12289ul,
      /* 9	*/ 24593ul,
      /* 10	*/ 49157ul,
      /* 11	*/ 98317ul,
      /* 12	*/ 196613ul,
      /* 13	*/ 393241ul,
      /* 14	*/ 786433ul,
      /* 15	*/ 1572869ul,
      /* 16	*/ 3145739ul,
      /* 17	*/ 6291469ul,
      /* 18	*/ 12582917ul,
      /* 19	*/ 25165843ul,
      /* 20	*/ 50331653ul,
      /* 21	*/ 100663319ul,
      /* 22	*/ 201326611ul,
      /* 23	*/ 402653189ul,
      /* 24	*/ 805306457ul,
      /* 25	*/ 1610612741,
      /* 26	*/ 3221225473ul,
      /* 27	*/ 4294967291ul
      /* Pot's good, let's play */
    };

} // namespace detail

PB_ASSOC_CLASS_T_DEC
inline void
PB_ASSOC_CLASS_C_DEC::
swap(PB_ASSOC_CLASS_C_DEC& /*r_other*/)
{ }

PB_ASSOC_CLASS_T_DEC
PB_ASSOC_CLASS_C_DEC::size_type
PB_ASSOC_CLASS_C_DEC::
get_init_size(size_type suggested_size) const
{
  return (get_nearest_larger_size_imp(suggested_size));
}

PB_ASSOC_CLASS_T_DEC
inline PB_ASSOC_CLASS_C_DEC::size_type
PB_ASSOC_CLASS_C_DEC::
get_nearest_larger_size(size_type cur_size) const
{
  PB_ASSOC_DBG_ONLY(assert_is_one_of_my_sizes(cur_size);)

    return (get_nearest_larger_size_imp(cur_size));
}

PB_ASSOC_CLASS_T_DEC
inline PB_ASSOC_CLASS_C_DEC::size_type
PB_ASSOC_CLASS_C_DEC::
get_nearest_smaller_size(size_type cur_size) const
{
  PB_ASSOC_DBG_ONLY(assert_is_one_of_my_sizes(cur_size);)

    return (*std::lower_bound(detail::s_a_sizes, detail::s_a_sizes + detail::num_distinct_sizes, cur_size - 1));
}

PB_ASSOC_CLASS_T_DEC
inline PB_ASSOC_CLASS_C_DEC::size_type
PB_ASSOC_CLASS_C_DEC::
get_nearest_larger_size_imp(size_type size) const
{
  const size_t* const p_upper =
    std::upper_bound(detail::s_a_sizes, detail::s_a_sizes + detail::num_distinct_sizes, size);

  return ((p_upper == detail::s_a_sizes + detail::num_distinct_sizes)?
	  size :
	  *p_upper);
}

#ifdef PB_ASSOC_HT_PRIME_SIZE_POLICY_DEBUG
PB_ASSOC_CLASS_T_DEC
void
PB_ASSOC_CLASS_C_DEC::
assert_is_one_of_my_sizes(size_type size)
{
  const size_t* const p_end =
    detail::s_a_sizes + detail::num_distinct_sizes;

  const size_t* const p_found =
    std::find(detail::s_a_sizes, p_end, size)

    PB_ASSOC_DBG_ASSERT(p_found != p_end);
}
#endif // #ifdef PB_ASSOC_HT_PRIME_SIZE_POLICY_DEBUG
