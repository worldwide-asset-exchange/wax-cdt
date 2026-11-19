/**
 *  @file
 *  @copyright defined in eosio.cdt/LICENSE.txt
 */

#include <limits>
#include <string>
#include <vector>

#include <eosio/tester.hpp>
#include <eosio/datastream.hpp>
#include <eosio/varint.hpp>

using std::numeric_limits;

using eosio::datastream;
using eosio::unsigned_int;
using eosio::signed_int;

static constexpr uint32_t u32min = numeric_limits<uint32_t>::min(); // 0
static constexpr uint32_t u32max = numeric_limits<uint32_t>::max(); // 4294967295

static constexpr int32_t i32min = numeric_limits<int32_t>::min(); // -2147483648
static constexpr int32_t i32max = numeric_limits<int32_t>::max(); //  2147483647

// Defined in `eosio.cdt/libraries/eosio/varint.hpp`
EOSIO_TEST_BEGIN(unsigned_int_type_test)
   //// unsigned_int(uint32_t)
   CHECK_EQUAL( unsigned_int{}.value, 0 )
   CHECK_EQUAL( unsigned_int{u32min}.value, 0 )
   CHECK_EQUAL( unsigned_int{u32max}.value, 4294967295 )

   //// unsigned_int(T)
   CHECK_EQUAL( unsigned_int{uint8_t{0}}.value,  0 )
   CHECK_EQUAL( unsigned_int{uint16_t{1}}.value, 1 )
   CHECK_EQUAL( unsigned_int{uint32_t{2}}.value, 2 )
   CHECK_EQUAL( unsigned_int{uint64_t{3}}.value, 3 )

   // -----------------
   // operator T()const
   CHECK_EQUAL( unsigned_int{0}.operator bool(), false )
   CHECK_EQUAL( unsigned_int{1}.operator bool(), true  )

   // ---------------------------------
   // unsigned_int& operator=(uint32_t)
   static const unsigned_int ui0{42};
   unsigned_int ui1{};

   ui1 = ui0;
   CHECK_EQUAL( ui0 == ui1, true )

   // ------------------------------------------------------------
   // friend bool operator==(const unsigned_int&, const uint32_t&)
   CHECK_EQUAL( unsigned_int{42} == uint32_t{42}, true  )
   CHECK_EQUAL( unsigned_int{42} == uint32_t{43}, false )

   // ------------------------------------------------------------
   // friend bool operator==(const uint32_t&, const unsigned_int&)
   CHECK_EQUAL( uint32_t{42} == unsigned_int{42}, true  )
   CHECK_EQUAL( uint32_t{43} == unsigned_int{42}, false )

   // ----------------------------------------------------------------
   // friend bool operator==(const unsigned_int&, const unsigned_int&)
   CHECK_EQUAL( unsigned_int{42} == unsigned_int{42}, true  )
   CHECK_EQUAL( unsigned_int{42} == unsigned_int{43}, false )

   // ------------------------------------------------------------
   // friend bool operator!=(const unsigned_int&, const uint32_t&)
   CHECK_EQUAL( unsigned_int{42} != uint32_t{42}, false )
   CHECK_EQUAL( unsigned_int{42} != uint32_t{43}, true  )

   // ------------------------------------------------------------
   // friend bool operator!=(const uint32_t&, const unsigned_int&)
   CHECK_EQUAL( uint32_t{42} != unsigned_int{42}, false )
   CHECK_EQUAL( uint32_t{43} != unsigned_int{42}, true  )

   // ----------------------------------------------------------------
   // friend bool operator!=(const unsigned_int&, const unsigned_int&)
   CHECK_EQUAL( unsigned_int{42} != unsigned_int{42}, false )
   CHECK_EQUAL( unsigned_int{42} != unsigned_int{43}, true  )

   // ------------------------------------------------------------
   // friend bool operator< (const unsigned_int&, const uint32_t&)
   CHECK_EQUAL( unsigned_int{42} < uint32_t{42}, false )
   CHECK_EQUAL( unsigned_int{42} < uint32_t{43}, true  )

   // ------------------------------------------------------------
   // friend bool operator< (const uint32_t&, const unsigned_int&)
   CHECK_EQUAL( uint32_t{42} < unsigned_int{42}, false )
   CHECK_EQUAL( uint32_t{42} < unsigned_int{43}, true  )

   // ----------------------------------------------------------------
   // friend bool operator< (const unsigned_int&, const unsigned_int&)
   CHECK_EQUAL( unsigned_int{42} < unsigned_int{42}, false )
   CHECK_EQUAL( unsigned_int{42} < unsigned_int{43}, true  )

   // ------------------------------------------------------------
   // friend bool operator>=(const unsigned_int&, const uint32_t&)
   CHECK_EQUAL( unsigned_int{42} >= uint32_t{42}, true  )
   CHECK_EQUAL( unsigned_int{42} >= uint32_t{43}, false )

   // ------------------------------------------------------------
   // friend bool operator>=(const uint32_t&, const unsigned_int&)
   CHECK_EQUAL( uint32_t{42} >= unsigned_int{42}, true  )
   CHECK_EQUAL( uint32_t{42} >= unsigned_int{43}, false )

   // ----------------------------------------------------------------
   // friend bool operator>=(const unsigned_int&, const unsigned_int&)
   CHECK_EQUAL( unsigned_int{42} >= unsigned_int{42}, true  )
   CHECK_EQUAL( unsigned_int{42} >= unsigned_int{43}, false )

   // ---------------------------------------------------------------
   // friend DataStream& operator<<(DataStream&, const unsigned_int&)
   // friend DataStream& operator>>(DataStream&, unsigned_int&)
   static constexpr uint16_t buffer_size{256};
   char datastream_buffer[buffer_size]; // Buffer for the datastream to point to

   datastream<const char*> ds{datastream_buffer, buffer_size};

   static const unsigned_int cui{42};
   unsigned_int ui{};
   ds << cui;
   ds.seekp(0);
   ds >> ui;
   CHECK_EQUAL( cui, ui)
EOSIO_TEST_END

// Defined in `eosio.cdt/libraries/eosio/varint.hpp`
EOSIO_TEST_BEGIN(signed_int_type_test)
   //// signed_int(uint32_t)
   CHECK_EQUAL( signed_int{}.value, 0 )
   CHECK_EQUAL( signed_int{i32min}.value, -2147483648 )
   CHECK_EQUAL( signed_int{i32max}.value,  2147483647 )

   // -----------------------
   // operator int32_t()const
   CHECK_EQUAL( signed_int{}.operator int32_t(), 0 )
   CHECK_EQUAL( signed_int{i32min}.operator int32_t(), -2147483648 )
   CHECK_EQUAL( signed_int{i32max}.operator int32_t(),  2147483647 )

   // --------------------------------
   //  signed_int& operator=(const T&)
   static const int8_t i8{0};
   static const int16_t i16{1};
   static const int32_t i32{2};
   static const int64_t i64{3};

   signed_int si0{};
   signed_int si1{};
   signed_int si2{};
   signed_int si3{};

   si0 = i8;
   si1 = i16;
   si2 = i32;
   si3 = i64;

   CHECK_EQUAL( si0.value, 0 )
   CHECK_EQUAL( si1.value, 1 )
   CHECK_EQUAL( si2.value, 2 )
   CHECK_EQUAL( si3.value, 3 )

   // --------------------------
   // signed_int operator++(int)
   signed_int si_post_inc0{0};
   signed_int si_post_inc1{1};
   CHECK_EQUAL( si_post_inc0++.value, 0 )
   CHECK_EQUAL( si_post_inc1++.value, 1 )

   // ------------------------
   // signed_int& operator++()
   signed_int si_pre_inc0{0};
   signed_int si_pre_inc1{1};
   CHECK_EQUAL( ++si_pre_inc0.value, 1 )
   CHECK_EQUAL( ++si_pre_inc1.value, 2 )

   // ------------------------------------------------------------
   // friend bool operator==(const signed_int&, const uint32_t&)
   CHECK_EQUAL( signed_int{42} == int32_t{42}, true  )
   CHECK_EQUAL( signed_int{42} == int32_t{43}, false )

   // ----------------------------------------------------------
   // friend bool operator==(const uint32_t&, const signed_int&)
   CHECK_EQUAL( int32_t{42} == signed_int{42}, true  )
   CHECK_EQUAL( int32_t{43} == signed_int{42}, false )

   // ------------------------------------------------------------
   // friend bool operator==(const signed_int&, const signed_int&)
   CHECK_EQUAL( signed_int{42} == signed_int{42}, true  )
   CHECK_EQUAL( signed_int{42} == signed_int{43}, false )

   // ----------------------------------------------------------
   // friend bool operator!=(const signed_int&, const uint32_t&)
   CHECK_EQUAL( signed_int{42} != int32_t{42}, false )
   CHECK_EQUAL( signed_int{42} != int32_t{43}, true  )

   // ----------------------------------------------------------
   // friend bool operator!=(const uint32_t&, const signed_int&)
   CHECK_EQUAL( int32_t{42} != signed_int{42}, false )
   CHECK_EQUAL( int32_t{43} != signed_int{42}, true  )

   // ------------------------------------------------------------
   // friend bool operator!=(const signed_int&, const signed_int&)
   CHECK_EQUAL( signed_int{42} != signed_int{42}, false )
   CHECK_EQUAL( signed_int{42} != signed_int{43}, true  )

   // ----------------------------------------------------------
   // friend bool operator< (const signed_int&, const uint32_t&)
   CHECK_EQUAL( signed_int{42} < int32_t{42}, false )
   CHECK_EQUAL( signed_int{42} < int32_t{43}, true  )

   // ----------------------------------------------------------
   // friend bool operator< (const uint32_t&, const signed_int&)
   CHECK_EQUAL( int32_t{42} < signed_int{42}, false )
   CHECK_EQUAL( int32_t{42} < signed_int{43}, true  )

   // ------------------------------------------------------------
   // friend bool operator< (const signed_int&, const signed_int&)
   CHECK_EQUAL( signed_int{42} < signed_int{42}, false )
   CHECK_EQUAL( signed_int{42} < signed_int{43}, true  )

   // ----------------------------------------------------------
   // friend bool operator>=(const signed_int&, const uint32_t&)
   CHECK_EQUAL( signed_int{42} >= int32_t{42}, true  )
   CHECK_EQUAL( signed_int{42} >= int32_t{43}, false )

   // ----------------------------------------------------------
   // friend bool operator>=(const uint32_t&, const signed_int&)
   CHECK_EQUAL( int32_t{42} >= signed_int{42}, true  )
   CHECK_EQUAL( int32_t{42} >= signed_int{43}, false )

   // ------------------------------------------------------------
   // friend bool operator>=(const signed_int&, const signed_int&)
   CHECK_EQUAL( signed_int{42} >= signed_int{42}, true  )
   CHECK_EQUAL( signed_int{42} >= signed_int{43}, false )

   // ----------------------------------------------------------------
   // friend DataStream& operator<<(DataStream& ds, const signed_int&)
   // friend DataStream& operator>>(DataStream&, signed_int&)
   static constexpr uint16_t buffer_size{256};
   char datastream_buffer[buffer_size]; // Buffer for the datastream to point to

   datastream<const char*> ds{datastream_buffer, buffer_size};

   static const signed_int csi{-42};
   signed_int a{44}, b{(1<<30)+2}, c{-35}, d{-(1<<30)-2}; // Small+, Small-, Large+, Large-
   signed_int aa, bb, cc, dd;
   ds << a << b << c << d;
   ds.seekp(0);
   ds >> aa >> bb >> cc >> dd;
   CHECK_EQUAL( a, aa )
   CHECK_EQUAL( b, bb )
   CHECK_EQUAL( c, cc )
   CHECK_EQUAL( d, dd )
EOSIO_TEST_END

EOSIO_TEST_BEGIN(unsigned_int_constexpr_test)
   //// unsigned_int(uint32_t)
   static_assert( unsigned_int{}.value == 0 );
   static_assert( unsigned_int{u32min}.value == 0 );
   static_assert( unsigned_int{u32max}.value == 4294967295);

   //// unsigned_int(T)
   static_assert( unsigned_int{uint8_t{0}}.value ==  0 );
   static_assert( unsigned_int{uint16_t{1}}.value == 1 );
   static_assert( unsigned_int{uint32_t{2}}.value == 2 );
   static_assert( unsigned_int{uint64_t{3}}.value == 3 );

   // -----------------
   // operator T()const
   static_assert( unsigned_int{0}.operator bool() == false );
   static_assert( unsigned_int{1}.operator bool() == true );

   // ---------------------------------
   // unsigned_int& operator=(uint32_t)
   constexpr unsigned_int ui0{42};
   constexpr unsigned_int ui1 = ui0;
   static_assert( ui0 == ui1 );

   // ------------------------------------------------------------
   // friend bool operator==(const unsigned_int&, const uint32_t&)
   static_assert( unsigned_int{42} == uint32_t{42} );
   static_assert( (unsigned_int{42} == uint32_t{43}) == false );

   // ------------------------------------------------------------
   // friend bool operator==(const uint32_t&, const unsigned_int&)
   static_assert( uint32_t{42} == unsigned_int{42} );
   static_assert( (uint32_t{43} == unsigned_int{42}) == false );

   // ----------------------------------------------------------------
   // friend bool operator==(const unsigned_int&, const unsigned_int&)
   static_assert( unsigned_int{42} == unsigned_int{42} );
   static_assert( (unsigned_int{42} == unsigned_int{43}) == false);

   // ------------------------------------------------------------
   // friend bool operator!=(const unsigned_int&, const uint32_t&)
   static_assert( (unsigned_int{42} != uint32_t{42}) == false );
   static_assert( unsigned_int{42} != uint32_t{43} );

   // ------------------------------------------------------------
   // friend bool operator!=(const uint32_t&, const unsigned_int&)
   static_assert( (uint32_t{42} != unsigned_int{42}) == false );
   static_assert( uint32_t{43} != unsigned_int{42} );

   // ----------------------------------------------------------------
   // friend bool operator!=(const unsigned_int&, const unsigned_int&)
   static_assert( (unsigned_int{42} != unsigned_int{42}) == false );
   static_assert( unsigned_int{42} != unsigned_int{43} );

   // ------------------------------------------------------------
   // friend bool operator< (const unsigned_int&, const uint32_t&)
   static_assert( (unsigned_int{42} < uint32_t{42}) == false );
   static_assert( unsigned_int{42} < uint32_t{43} );

   // ------------------------------------------------------------
   // friend bool operator< (const uint32_t&, const unsigned_int&)
   static_assert( (uint32_t{42} < unsigned_int{42}) == false );
   static_assert( uint32_t{42} < unsigned_int{43} );

   // ----------------------------------------------------------------
   // friend bool operator< (const unsigned_int&, const unsigned_int&)
   static_assert( (unsigned_int{42} < unsigned_int{42}) == false );
   static_assert( unsigned_int{42} < unsigned_int{43} );

   // ------------------------------------------------------------
   // friend bool operator>=(const unsigned_int&, const uint32_t&)
   static_assert( unsigned_int{42} >= uint32_t{42} );
   static_assert( (unsigned_int{42} >= uint32_t{43}) == false );

   // ------------------------------------------------------------
   // friend bool operator>=(const uint32_t&, const unsigned_int&)
   static_assert( uint32_t{42} >= unsigned_int{42} );
   static_assert( (uint32_t{42} >= unsigned_int{43}) == false  );

   // ----------------------------------------------------------------
   // friend bool operator>=(const unsigned_int&, const unsigned_int&)
   static_assert( unsigned_int{42} >= unsigned_int{42} );
   static_assert( (unsigned_int{42} >= unsigned_int{43}) == false  );

   // ----------
   // misc tests
   static_assert( unsigned_int{0xff}.value == 255 );     // 1 byte
   static_assert( unsigned_int{0xffff}.value == 65535 ); // 2 bytes
   static_assert( unsigned_int{0xffffff}.value == 16777215 ); // 3 bytes
   static_assert( unsigned_int{0xffffffff}.value == 4294967295 ); // 4 bytes
   static_assert( unsigned_int{100l}.value == 100 );  // cast from long
   static_assert( sizeof(unsigned_int{0xf}) == 4 );
EOSIO_TEST_END

EOSIO_TEST_BEGIN(signed_int_constexpr_test)
   //// signed_int(uint32_t)
   static_assert( signed_int{}.value == 0 );
   static_assert( signed_int{i32min}.value == -2147483648 );
   static_assert( signed_int{i32max}.value ==  2147483647 );

   // -----------------------
   // operator int32_t()const
   static_assert( signed_int{}.operator int32_t() == 0 );
   static_assert( signed_int{i32min}.operator int32_t() == -2147483648 );
   static_assert( signed_int{i32max}.operator int32_t() ==  2147483647 );

   // --------------------------------
   //  signed_int& operator=(const T&)
   constexpr int8_t i8{0};
   constexpr int16_t i16{1};
   constexpr int32_t i32{2};
   constexpr int64_t i64{3};

   constexpr signed_int si0 = i8;
   constexpr signed_int si1 = i16;
   constexpr signed_int si2 = i32;
   constexpr signed_int si3 = i64;

   static_assert( si0.value == 0 );
   static_assert( si1.value == 1 );
   static_assert( si2.value == 2 );
   static_assert( si3.value == 3 );

   // --------------------------
   // signed_int operator++(int)
   constexpr signed_int si_post_inc0{ signed_int{0}++ };
   constexpr signed_int si_post_inc1{ signed_int{1}++ };
   static_assert( si_post_inc0.value == 0 );
   static_assert( si_post_inc1.value == 1 );

   // ------------------------
   // signed_int& operator++()
   constexpr signed_int si_pre_inc0{ ++signed_int{0} };
   constexpr signed_int si_pre_inc1{ ++signed_int{1} };
   static_assert( si_pre_inc0.value == 1 );
   static_assert( si_pre_inc1.value == 2 );

   // ------------------------------------------------------------
   // friend bool operator==(const signed_int&, const uint32_t&)
   static_assert( signed_int{42} == int32_t{42} );
   static_assert( (signed_int{42} == int32_t{43}) == false );

   // ----------------------------------------------------------
   // friend bool operator==(const uint32_t&, const signed_int&)
   static_assert( int32_t{42} == signed_int{42} );
   static_assert( (int32_t{43} == signed_int{42}) == false );

   // ------------------------------------------------------------
   // friend bool operator==(const signed_int&, const signed_int&)
   static_assert( signed_int{42} == signed_int{42} );
   static_assert( (signed_int{42} == signed_int{43}) == false );

   // ----------------------------------------------------------
   // friend bool operator!=(const signed_int&, const uint32_t&)
   static_assert( (signed_int{42} != int32_t{42}) == false );
   static_assert( signed_int{42} != int32_t{43} );

   // ----------------------------------------------------------
   // friend bool operator!=(const uint32_t&, const signed_int&)
   static_assert( (int32_t{42} != signed_int{42}) == false );
   static_assert( int32_t{43} != signed_int{42} );

   // ------------------------------------------------------------
   // friend bool operator!=(const signed_int&, const signed_int&)
   static_assert( (signed_int{42} != signed_int{42}) == false );
   static_assert( signed_int{42} != signed_int{43} );

   // ----------------------------------------------------------
   // friend bool operator< (const signed_int&, const uint32_t&)
   static_assert( (signed_int{42} < int32_t{42}) == false );
   static_assert( signed_int{42} < int32_t{43} );

   // ----------------------------------------------------------
   // friend bool operator< (const uint32_t&, const signed_int&)
   static_assert( (int32_t{42} < signed_int{42}) == false );
   static_assert( int32_t{42} < signed_int{43} );

   // ------------------------------------------------------------
   // friend bool operator< (const signed_int&, const signed_int&)
   static_assert( (signed_int{42} < signed_int{42}) == false );
   static_assert( signed_int{42} < signed_int{43} );

   // ----------------------------------------------------------
   // friend bool operator>=(const signed_int&, const uint32_t&)
   static_assert( signed_int{42} >= int32_t{42} );
   static_assert( (signed_int{42} >= int32_t{43}) == false );

   // ----------------------------------------------------------
   // friend bool operator>=(const uint32_t&, const signed_int&)
   static_assert( int32_t{42} >= signed_int{42} );
   static_assert( (int32_t{42} >= signed_int{43}) == false );

   // ------------------------------------------------------------
   // friend bool operator>=(const signed_int&, const signed_int&)
   static_assert( signed_int{42} >= signed_int{42} );
   static_assert( (signed_int{42} >= signed_int{43}) == false );

   // ----------
   // misc tests
   static_assert( signed_int{0xff}.value == 255 );     // 1 byte
   static_assert( signed_int{0xffff}.value == 65535 ); // 2 bytes
   static_assert( signed_int{0xffffff}.value == 16777215 ); // 3 bytes
   static_assert( signed_int{0x7fffffff}.value == 2147483647 ); // 4 bytes
   static_assert( signed_int{-0x7fffffff}.value == -2147483647 ); // 4 bytes
   static_assert( signed_int{-0x80000000l}.value == -2147483648 ); // 4 bytes
   static_assert( signed_int{100u}.value == 100 ); // cast from unsigned
   static_assert( sizeof(signed_int{0xf}) == 4 );
EOSIO_TEST_END

// The contract-side varint readers have to consume exactly the bytes the node's readers consume
// (fc::raw::unpack) and produce the same value, otherwise a contract and the node read two
// different objects out of one byte sequence. The node reads an `unsigned_int` from at most five
// bytes (`by < 32`).
template<typename VarInt, size_t N>
static bool decodes_as( const uint8_t (&bytes)[N], decltype(VarInt::value) value, size_t consumed ) {
   datastream<const char*> ds{reinterpret_cast<const char*>(bytes), N};
   VarInt vi{};
   ds >> vi;
   return vi.value == value && ds.tellp() == consumed;
}

EOSIO_TEST_BEGIN(unsigned_int_decode_bound_test)
   // Canonical encodings
   { const uint8_t b[] = {0x00, 0xaa};                               CHECK_EQUAL( decodes_as<unsigned_int>(b, 0u, 1), true ) }
   { const uint8_t b[] = {0x7f, 0xaa};                               CHECK_EQUAL( decodes_as<unsigned_int>(b, 127u, 1), true ) }
   { const uint8_t b[] = {0x80, 0x01, 0xaa};                         CHECK_EQUAL( decodes_as<unsigned_int>(b, 128u, 2), true ) }
   { const uint8_t b[] = {0xff, 0xff, 0xff, 0xff, 0x0f, 0xaa};       CHECK_EQUAL( decodes_as<unsigned_int>(b, u32max, 5), true ) }

   // Padded (non-minimal) encodings within five bytes: accepted, as the node accepts them
   { const uint8_t b[] = {0x80, 0x00, 0xaa};                         CHECK_EQUAL( decodes_as<unsigned_int>(b, 0u, 2), true ) }
   { const uint8_t b[] = {0x81, 0x80, 0x80, 0x80, 0x00, 0xaa};       CHECK_EQUAL( decodes_as<unsigned_int>(b, 1u, 5), true ) }

   // Over-long encodings: the fifth byte ends the value even with its continuation bit set
   { const uint8_t b[] = {0x80, 0x80, 0x80, 0x80, 0x80, 0x00};       CHECK_EQUAL( decodes_as<unsigned_int>(b, 0u, 5), true ) }
   { const uint8_t b[] = {0x81, 0x80, 0x80, 0x80, 0x80, 0x7f, 0x7f}; CHECK_EQUAL( decodes_as<unsigned_int>(b, 1u, 5), true ) }
   { const uint8_t b[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01}; CHECK_EQUAL( decodes_as<unsigned_int>(b, u32max, 5), true ) }

   // High bits of the fifth byte do not fit in 32 bits and are dropped
   { const uint8_t b[] = {0xff, 0xff, 0xff, 0xff, 0x7f, 0xaa};       CHECK_EQUAL( decodes_as<unsigned_int>(b, u32max, 5), true ) }
   { const uint8_t b[] = {0x80, 0x80, 0x80, 0x80, 0x70, 0xaa};       CHECK_EQUAL( decodes_as<unsigned_int>(b, 0u, 5), true ) }

   // End of input: the fifth byte may be the last one, fewer than five unterminated bytes may not
   { const uint8_t b[] = {0x80, 0x80, 0x80, 0x80, 0x80};             CHECK_EQUAL( decodes_as<unsigned_int>(b, 0u, 5), true ) }
   {
      static const uint8_t b[] = {0x80, 0x80, 0x80, 0x80};
      CHECK_ASSERT( "get", ([]() {
         datastream<const char*> ds{reinterpret_cast<const char*>(b), sizeof(b)};
         unsigned_int vi{};
         ds >> vi;
      }) )
   }

   // Length prefixes are read through unsigned_int, so the content follows the fifth byte
   {
      const uint8_t b[] = {0x82, 0x80, 0x80, 0x80, 0x80, 0x68, 0x69, 0x21};
      datastream<const char*> ds{reinterpret_cast<const char*>(b), sizeof(b)};
      std::string s;
      ds >> s;
      CHECK_EQUAL( s == "hi", true )
      CHECK_EQUAL( ds.tellp(), 7 )
   }
   {
      const uint8_t b[] = {0x81, 0x80, 0x80, 0x80, 0x80, 0x41, 0x42};
      datastream<const char*> ds{reinterpret_cast<const char*>(b), sizeof(b)};
      std::vector<char> v;
      ds >> v;
      CHECK_EQUAL( v.size(), 1 )
      CHECK_EQUAL( v[0], 0x41 )
      CHECK_EQUAL( ds.tellp(), 6 )
   }
EOSIO_TEST_END

// The node reads a `signed_int` (ABI `varint32`) without a bound, so this reader has none either:
// an over-long encoding is consumed to its terminating byte.
EOSIO_TEST_BEGIN(signed_int_decode_test)
   // Canonical encodings (zig-zag)
   { const uint8_t b[] = {0x00, 0xaa};                               CHECK_EQUAL( decodes_as<signed_int>(b, 0, 1), true ) }
   { const uint8_t b[] = {0x01, 0xaa};                               CHECK_EQUAL( decodes_as<signed_int>(b, -1, 1), true ) }
   { const uint8_t b[] = {0x80, 0x01, 0xaa};                         CHECK_EQUAL( decodes_as<signed_int>(b, 64, 2), true ) }
   { const uint8_t b[] = {0xfe, 0xff, 0xff, 0xff, 0x0f, 0xaa};       CHECK_EQUAL( decodes_as<signed_int>(b, i32max, 5), true ) }
   { const uint8_t b[] = {0xff, 0xff, 0xff, 0xff, 0x0f, 0xaa};       CHECK_EQUAL( decodes_as<signed_int>(b, i32min, 5), true ) }

   // Padded within five bytes
   { const uint8_t b[] = {0x80, 0x00, 0xaa};                         CHECK_EQUAL( decodes_as<signed_int>(b, 0, 2), true ) }

   // Over-long: the sixth byte belongs to the value, as on the node
   { const uint8_t b[] = {0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0xaa}; CHECK_EQUAL( decodes_as<signed_int>(b, 0, 6), true ) }
EOSIO_TEST_END

int main(int argc, char* argv[]) {
   bool verbose = false;
   if( argc >= 2 && std::strcmp( argv[1], "-v" ) == 0 ) {
      verbose = true;
   }
   silence_output(!verbose);

   EOSIO_TEST(unsigned_int_type_test)
   EOSIO_TEST(signed_int_type_test);
   EOSIO_TEST(unsigned_int_constexpr_test);
   EOSIO_TEST(signed_int_constexpr_test);
   EOSIO_TEST(unsigned_int_decode_bound_test);
   EOSIO_TEST(signed_int_decode_test);
   return has_failed();
}
