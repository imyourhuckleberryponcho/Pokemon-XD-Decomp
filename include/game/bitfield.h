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
#define GC_INIT2(v1, v2) v1, v2
#define GC_INIT3(v1, v2, v3) v1, v2, v3
#define GC_INIT4(v1, v2, v3, v4) v1, v2, v3, v4
#define GC_INIT5(v1, v2, v3, v4, v5) v1, v2, v3, v4, v5
#define GC_INIT6(v1, v2, v3, v4, v5, v6) v1, v2, v3, v4, v5, v6
#define GC_INIT7(v1, v2, v3, v4, v5, v6, v7) v1, v2, v3, v4, v5, v6, v7
#define GC_INIT8(v1, v2, v3, v4, v5, v6, v7, v8) v1, v2, v3, v4, v5, v6, v7, v8
#define GC_INIT9(v1, v2, v3, v4, v5, v6, v7, v8, v9) v1, v2, v3, v4, v5, v6, v7, v8, v9
#define GC_INIT10(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10
#define GC_INIT11(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11
#define GC_INIT12(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12
#define GC_INIT13(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13
#define GC_INIT14(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14
#define GC_INIT15(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15
#define GC_INIT16(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16
#define GC_INIT17(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17
#define GC_INIT18(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18
#define GC_INIT19(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
#define GC_INIT20(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20
#define GC_INIT21(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21
#define GC_INIT22(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22
#define GC_INIT23(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23
#define GC_INIT24(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24
#define GC_INIT25(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25
#define GC_INIT26(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26
#define GC_INIT27(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27
#define GC_INIT28(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28
#define GC_INIT29(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
#define GC_INIT30(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30
#define GC_INIT31(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31
#define GC_INIT32(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32) v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32
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
#define GC_INIT2(v1, v2) v2, v1
#define GC_INIT3(v1, v2, v3) v3, v2, v1
#define GC_INIT4(v1, v2, v3, v4) v4, v3, v2, v1
#define GC_INIT5(v1, v2, v3, v4, v5) v5, v4, v3, v2, v1
#define GC_INIT6(v1, v2, v3, v4, v5, v6) v6, v5, v4, v3, v2, v1
#define GC_INIT7(v1, v2, v3, v4, v5, v6, v7) v7, v6, v5, v4, v3, v2, v1
#define GC_INIT8(v1, v2, v3, v4, v5, v6, v7, v8) v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT9(v1, v2, v3, v4, v5, v6, v7, v8, v9) v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT10(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT11(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11) v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT12(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12) v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT13(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13) v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT14(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14) v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT15(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15) v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT16(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16) v16, v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT17(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17) v17, v16, v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT18(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18) v18, v17, v16, v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT19(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19) v19, v18, v17, v16, v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT20(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20) v20, v19, v18, v17, v16, v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT21(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21) v21, v20, v19, v18, v17, v16, v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT22(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22) v22, v21, v20, v19, v18, v17, v16, v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT23(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23) v23, v22, v21, v20, v19, v18, v17, v16, v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT24(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24) v24, v23, v22, v21, v20, v19, v18, v17, v16, v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT25(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25) v25, v24, v23, v22, v21, v20, v19, v18, v17, v16, v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT26(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26) v26, v25, v24, v23, v22, v21, v20, v19, v18, v17, v16, v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT27(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27) v27, v26, v25, v24, v23, v22, v21, v20, v19, v18, v17, v16, v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT28(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28) v28, v27, v26, v25, v24, v23, v22, v21, v20, v19, v18, v17, v16, v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT29(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29) v29, v28, v27, v26, v25, v24, v23, v22, v21, v20, v19, v18, v17, v16, v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT30(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30) v30, v29, v28, v27, v26, v25, v24, v23, v22, v21, v20, v19, v18, v17, v16, v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT31(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31) v31, v30, v29, v28, v27, v26, v25, v24, v23, v22, v21, v20, v19, v18, v17, v16, v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#define GC_INIT32(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32) v32, v31, v30, v29, v28, v27, v26, v25, v24, v23, v22, v21, v20, v19, v18, v17, v16, v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1
#endif

#endif
