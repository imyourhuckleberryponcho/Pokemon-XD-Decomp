#ifndef GAME_BITFIELD_H
#define GAME_BITFIELD_H

#ifdef __MWERKS__
#define GC_BITS2(f1, f2) f1; f2;
#define GC_BITS3(f1, f2, f3) f1; f2; f3;
#define GC_BITS4(f1, f2, f3, f4) f1; f2; f3; f4;
#define GC_BITS5(f1, f2, f3, f4, f5) f1; f2; f3; f4; f5;
#define GC_BITS6(f1, f2, f3, f4, f5, f6) f1; f2; f3; f4; f5; f6;
#define GC_BITS7(f1, f2, f3, f4, f5, f6, f7) f1; f2; f3; f4; f5; f6; f7;
#define GC_BITS8(f1, f2, f3, f4, f5, f6, f7, f8) f1; f2; f3; f4; f5; f6; f7; f8;
#define GC_BITS9(f1, f2, f3, f4, f5, f6, f7, f8, f9) f1; f2; f3; f4; f5; f6; f7; f8; f9;
#define GC_BITS10(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10;
#define GC_BITS11(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11;
#define GC_BITS12(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12;
#define GC_BITS13(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12; f13;
#define GC_BITS14(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12; f13; f14;
#define GC_BITS15(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12; f13; f14; f15;
#define GC_BITS16(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12; f13; f14; f15; f16;
#define GC_BITS17(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12; f13; f14; f15; f16; f17;
#define GC_BITS18(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12; f13; f14; f15; f16; f17; f18;
#define GC_BITS19(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12; f13; f14; f15; f16; f17; f18; f19;
#define GC_BITS20(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12; f13; f14; f15; f16; f17; f18; f19; f20;
#define GC_BITS21(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12; f13; f14; f15; f16; f17; f18; f19; f20; f21;
#define GC_BITS22(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12; f13; f14; f15; f16; f17; f18; f19; f20; f21; f22;
#define GC_BITS23(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12; f13; f14; f15; f16; f17; f18; f19; f20; f21; f22; f23;
#define GC_BITS24(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12; f13; f14; f15; f16; f17; f18; f19; f20; f21; f22; f23; f24;
#define GC_BITS25(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12; f13; f14; f15; f16; f17; f18; f19; f20; f21; f22; f23; f24; f25;
#define GC_BITS26(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25, f26) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12; f13; f14; f15; f16; f17; f18; f19; f20; f21; f22; f23; f24; f25; f26;
#define GC_BITS27(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25, f26, f27) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12; f13; f14; f15; f16; f17; f18; f19; f20; f21; f22; f23; f24; f25; f26; f27;
#define GC_BITS28(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25, f26, f27, f28) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12; f13; f14; f15; f16; f17; f18; f19; f20; f21; f22; f23; f24; f25; f26; f27; f28;
#define GC_BITS29(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25, f26, f27, f28, f29) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12; f13; f14; f15; f16; f17; f18; f19; f20; f21; f22; f23; f24; f25; f26; f27; f28; f29;
#define GC_BITS30(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25, f26, f27, f28, f29, f30) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12; f13; f14; f15; f16; f17; f18; f19; f20; f21; f22; f23; f24; f25; f26; f27; f28; f29; f30;
#define GC_BITS31(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25, f26, f27, f28, f29, f30, f31) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12; f13; f14; f15; f16; f17; f18; f19; f20; f21; f22; f23; f24; f25; f26; f27; f28; f29; f30; f31;
#define GC_BITS32(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25, f26, f27, f28, f29, f30, f31, f32) f1; f2; f3; f4; f5; f6; f7; f8; f9; f10; f11; f12; f13; f14; f15; f16; f17; f18; f19; f20; f21; f22; f23; f24; f25; f26; f27; f28; f29; f30; f31; f32;
#else
#define GC_BITS2(f1, f2) f2; f1;
#define GC_BITS3(f1, f2, f3) f3; f2; f1;
#define GC_BITS4(f1, f2, f3, f4) f4; f3; f2; f1;
#define GC_BITS5(f1, f2, f3, f4, f5) f5; f4; f3; f2; f1;
#define GC_BITS6(f1, f2, f3, f4, f5, f6) f6; f5; f4; f3; f2; f1;
#define GC_BITS7(f1, f2, f3, f4, f5, f6, f7) f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS8(f1, f2, f3, f4, f5, f6, f7, f8) f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS9(f1, f2, f3, f4, f5, f6, f7, f8, f9) f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS10(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10) f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS11(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11) f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS12(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12) f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS13(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13) f13; f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS14(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14) f14; f13; f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS15(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15) f15; f14; f13; f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS16(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16) f16; f15; f14; f13; f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS17(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17) f17; f16; f15; f14; f13; f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS18(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18) f18; f17; f16; f15; f14; f13; f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS19(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19) f19; f18; f17; f16; f15; f14; f13; f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS20(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20) f20; f19; f18; f17; f16; f15; f14; f13; f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS21(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21) f21; f20; f19; f18; f17; f16; f15; f14; f13; f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS22(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22) f22; f21; f20; f19; f18; f17; f16; f15; f14; f13; f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS23(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23) f23; f22; f21; f20; f19; f18; f17; f16; f15; f14; f13; f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS24(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24) f24; f23; f22; f21; f20; f19; f18; f17; f16; f15; f14; f13; f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS25(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25) f25; f24; f23; f22; f21; f20; f19; f18; f17; f16; f15; f14; f13; f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS26(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25, f26) f26; f25; f24; f23; f22; f21; f20; f19; f18; f17; f16; f15; f14; f13; f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS27(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25, f26, f27) f27; f26; f25; f24; f23; f22; f21; f20; f19; f18; f17; f16; f15; f14; f13; f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS28(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25, f26, f27, f28) f28; f27; f26; f25; f24; f23; f22; f21; f20; f19; f18; f17; f16; f15; f14; f13; f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS29(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25, f26, f27, f28, f29) f29; f28; f27; f26; f25; f24; f23; f22; f21; f20; f19; f18; f17; f16; f15; f14; f13; f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS30(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25, f26, f27, f28, f29, f30) f30; f29; f28; f27; f26; f25; f24; f23; f22; f21; f20; f19; f18; f17; f16; f15; f14; f13; f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS31(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25, f26, f27, f28, f29, f30, f31) f31; f30; f29; f28; f27; f26; f25; f24; f23; f22; f21; f20; f19; f18; f17; f16; f15; f14; f13; f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#define GC_BITS32(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25, f26, f27, f28, f29, f30, f31, f32) f32; f31; f30; f29; f28; f27; f26; f25; f24; f23; f22; f21; f20; f19; f18; f17; f16; f15; f14; f13; f12; f11; f10; f9; f8; f7; f6; f5; f4; f3; f2; f1;
#endif

#endif
