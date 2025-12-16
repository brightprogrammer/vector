#include <stdio.h>
char flag[256] = { 0 };
unsigned long hash = 0;
char mem[256] = { 0 };
int main(void)
{
    printf("enter flag: ");
    fgets(flag, 256, stdin);
    if (flag[3] == '6') {
        if (flag[5] == 'n') {
            hash ^= 36354093219671485;
            printf("found %c at %d\n", 110, 5);
            if (flag[1] == 'h') {
                hash ^= 42375064963616033;
                printf("found %c at %d\n", 104, 1);
                if (flag[0] == 'i') {
                    hash ^= 55726923896737270;
                    printf("found %c at %d\n", 105, 0);
                    if (flag[27] == 'q') {
                        hash ^= 49660435826214599;
                        printf("found %c at %d\n", 113, 27);
                        if (flag[161] == 'a') {
                            hash ^= 42694984187916221;
                            printf("found %c at %d\n", 97, 161);
                            if (flag[168] == 'g') {
                                hash ^= 57406806889248358;
                                printf("found %c at %d\n", 103, 168);
                                if (flag[45] == 'p') {
                                    hash ^= 60431009832769561;
                                    printf("found %c at %d\n", 112, 45);
                                    if (flag[167] == 'b') {
                                        hash ^= 37860339663447082;
                                        printf("found %c at %d\n", 98, 167);
                                        if (flag[76] == 'z') {
                                            hash ^= 47644563937576010;
                                            printf("found %c at %d\n", 122, 76);
                                            if (flag[1] == 'I') {
                                                hash ^= 57607538467461542;
                                                printf("found %c at %d\n", 73, 1);
                                            } else {
                                                hash ^= 55227805483796879;
                                            }
                                        } else if (flag[163] == 'J') {
                                            hash ^= 57954008163397951;
                                            printf("found %c at %d\n", 74, 163);
                                        } else {
                                            hash ^= 63327345059897624;
                                        }
                                    } else if (flag[99] == 'D') {
                                        hash ^= 69932444739965702;
                                        printf("found %c at %d\n", 68, 99);
                                        if (flag[48] == '3') {
                                            hash ^= 41097713084759958;
                                            printf("found %c at %d\n", 51, 48);
                                        } else if (flag[190] == 'd') {
                                            hash ^= 46983042137344643;
                                            printf("found %c at %d\n", 100, 190);
                                        } else {
                                            hash ^= 52846541178881066;
                                        }
                                    } else {
                                        hash ^= 69492408927628647;
                                    }
                                } else if (flag[104] == '7') {
                                    hash ^= 53430158739278028;
                                    printf("found %c at %d\n", 55, 104);
                                    if (flag[192] == 'B') {
                                        hash ^= 55381993114991535;
                                        printf("found %c at %d\n", 66, 192);
                                        if (flag[216] == '4') {
                                            hash ^= 44178313167070650;
                                            printf("found %c at %d\n", 52, 216);
                                        } else if (flag[110] == 'I') {
                                            hash ^= 63881303149009304;
                                            printf("found %c at %d\n", 73, 110);
                                        } else {
                                            hash ^= 63461866439710135;
                                        }
                                    } else if (flag[39] == 'f') {
                                        hash ^= 44918076940745018;
                                        printf("found %c at %d\n", 102, 39);
                                        if (flag[177] == '4') {
                                            hash ^= 47351191261626936;
                                            printf("found %c at %d\n", 52, 177);
                                        } else if (flag[49] == 'D') {
                                            hash ^= 65922330275768546;
                                            printf("found %c at %d\n", 68, 49);
                                        } else {
                                            hash ^= 47395233635020213;
                                        }
                                    } else {
                                        hash ^= 69468815082228594;
                                    }
                                } else {
                                    hash ^= 68290411670499933;
                                }
                            } else if (flag[17] == 'p') {
                                hash ^= 58939521356166832;
                                printf("found %c at %d\n", 112, 17);
                                if (flag[210] == 'U') {
                                    hash ^= 67783783857582580;
                                    printf("found %c at %d\n", 85, 210);
                                    if (flag[92] == 'a') {
                                        hash ^= 52072879218534166;
                                        printf("found %c at %d\n", 97, 92);
                                        if (flag[121] == 'k') {
                                            hash ^= 44002667972502737;
                                            printf("found %c at %d\n", 107, 121);
                                        } else if (flag[62] == '9') {
                                            hash ^= 67529589640388930;
                                            printf("found %c at %d\n", 57, 62);
                                        } else {
                                            hash ^= 63436537579192230;
                                        }
                                    } else if (flag[195] == 'R') {
                                        hash ^= 43612870823958501;
                                        printf("found %c at %d\n", 82, 195);
                                        if (flag[81] == 'h') {
                                            hash ^= 54826079637066232;
                                            printf("found %c at %d\n", 104, 81);
                                        } else if (flag[167] == 'N') {
                                            hash ^= 50483034399618829;
                                            printf("found %c at %d\n", 78, 167);
                                        } else {
                                            hash ^= 50624338635675893;
                                        }
                                    } else {
                                        hash ^= 48828530356890138;
                                    }
                                } else if (flag[25] == 'z') {
                                    hash ^= 51574903432550357;
                                    printf("found %c at %d\n", 122, 25);
                                    if (flag[11] == 'R') {
                                        hash ^= 43653698739243144;
                                        printf("found %c at %d\n", 82, 11);
                                        if (flag[139] == 'm') {
                                            hash ^= 68751332066596112;
                                            printf("found %c at %d\n", 109, 139);
                                        } else if (flag[68] == 'n') {
                                            hash ^= 60322096390444848;
                                            printf("found %c at %d\n", 110, 68);
                                        } else {
                                            hash ^= 59036783849868801;
                                        }
                                    } else if (flag[185] == 'n') {
                                        hash ^= 68493975803064979;
                                        printf("found %c at %d\n", 110, 185);
                                        if (flag[206] == 's') {
                                            hash ^= 68676080596205562;
                                            printf("found %c at %d\n", 115, 206);
                                        } else if (flag[226] == '5') {
                                            hash ^= 51612108286902773;
                                            printf("found %c at %d\n", 53, 226);
                                        } else {
                                            hash ^= 44669207714799793;
                                        }
                                    } else {
                                        hash ^= 36846097783844712;
                                    }
                                } else {
                                    hash ^= 39726874747463950;
                                }
                            } else {
                                hash ^= 41636725271632838;
                            }
                        } else if (flag[243] == 'T') {
                            hash ^= 42887198759067667;
                            printf("found %c at %d\n", 84, 243);
                            if (flag[142] == '_') {
                                hash ^= 45405039392002062;
                                printf("found %c at %d\n", 95, 142);
                                if (flag[157] == '0') {
                                    hash ^= 66027411443527980;
                                    printf("found %c at %d\n", 48, 157);
                                    if (flag[71] == 'y') {
                                        hash ^= 65332821154336224;
                                        printf("found %c at %d\n", 121, 71);
                                        if (flag[181] == 'J') {
                                            hash ^= 69772690124191317;
                                            printf("found %c at %d\n", 74, 181);
                                        } else if (flag[166] == 't') {
                                            hash ^= 68894449618110184;
                                            printf("found %c at %d\n", 116, 166);
                                        } else {
                                            hash ^= 47541293948648501;
                                        }
                                    } else if (flag[225] == 'y') {
                                        hash ^= 59225081929521717;
                                        printf("found %c at %d\n", 121, 225);
                                        if (flag[203] == 'c') {
                                            hash ^= 71639509325139372;
                                            printf("found %c at %d\n", 99, 203);
                                        } else if (flag[152] == 'S') {
                                            hash ^= 57931349476487776;
                                            printf("found %c at %d\n", 83, 152);
                                        } else {
                                            hash ^= 38701646760080590;
                                        }
                                    } else {
                                        hash ^= 38420445423691069;
                                    }
                                } else if (flag[2] == '2') {
                                    hash ^= 53117076438048078;
                                    printf("found %c at %d\n", 50, 2);
                                    if (flag[243] == 'u') {
                                        hash ^= 70569873441518419;
                                        printf("found %c at %d\n", 117, 243);
                                        if (flag[125] == '6') {
                                            hash ^= 50047889370061486;
                                            printf("found %c at %d\n", 54, 125);
                                        } else if (flag[114] == 'O') {
                                            hash ^= 70533134529272124;
                                            printf("found %c at %d\n", 79, 114);
                                        } else {
                                            hash ^= 60324050433258081;
                                        }
                                    } else if (flag[231] == '8') {
                                        hash ^= 55914101282577767;
                                        printf("found %c at %d\n", 56, 231);
                                        if (flag[204] == 'z') {
                                            hash ^= 51933325219373842;
                                            printf("found %c at %d\n", 122, 204);
                                        } else if (flag[233] == 'I') {
                                            hash ^= 47295006798337928;
                                            printf("found %c at %d\n", 73, 233);
                                        } else {
                                            hash ^= 57632611873330353;
                                        }
                                    } else {
                                        hash ^= 55229080250578255;
                                    }
                                } else {
                                    hash ^= 60133595560178312;
                                }
                            } else if (flag[80] == 'l') {
                                hash ^= 37213273811563500;
                                printf("found %c at %d\n", 108, 80);
                                if (flag[216] == 'P') {
                                    hash ^= 50043567284091551;
                                    printf("found %c at %d\n", 80, 216);
                                    if (flag[74] == 't') {
                                        hash ^= 59276110154826308;
                                        printf("found %c at %d\n", 116, 74);
                                        if (flag[68] == 'u') {
                                            hash ^= 54474935103171353;
                                            printf("found %c at %d\n", 117, 68);
                                        } else if (flag[219] == 'Z') {
                                            hash ^= 40824367227470946;
                                            printf("found %c at %d\n", 90, 219);
                                        } else {
                                            hash ^= 58941918800333571;
                                        }
                                    } else if (flag[178] == 'u') {
                                        hash ^= 47702019056479023;
                                        printf("found %c at %d\n", 117, 178);
                                        if (flag[178] == 'U') {
                                            hash ^= 44155297852728090;
                                            printf("found %c at %d\n", 85, 178);
                                        } else if (flag[41] == 'v') {
                                            hash ^= 66296361276657481;
                                            printf("found %c at %d\n", 118, 41);
                                        } else {
                                            hash ^= 71382246103969029;
                                        }
                                    } else {
                                        hash ^= 67856247440568467;
                                    }
                                } else if (flag[6] == 'b') {
                                    hash ^= 52011826441964248;
                                    printf("found %c at %d\n", 98, 6);
                                    if (flag[130] == 'u') {
                                        hash ^= 53444644842264669;
                                        printf("found %c at %d\n", 117, 130);
                                        if (flag[224] == 'T') {
                                            hash ^= 68223384228031644;
                                            printf("found %c at %d\n", 84, 224);
                                        } else if (flag[113] == 'O') {
                                            hash ^= 63470896643606834;
                                            printf("found %c at %d\n", 79, 113);
                                        } else {
                                            hash ^= 59101409580661475;
                                        }
                                    } else if (flag[157] == 'c') {
                                        hash ^= 71854845399979126;
                                        printf("found %c at %d\n", 99, 157);
                                        if (flag[118] == '9') {
                                            hash ^= 44371042392126358;
                                            printf("found %c at %d\n", 57, 118);
                                        } else if (flag[75] == 'd') {
                                            hash ^= 59945633977593523;
                                            printf("found %c at %d\n", 100, 75);
                                        } else {
                                            hash ^= 56421808553158326;
                                        }
                                    } else {
                                        hash ^= 55802669286281230;
                                    }
                                } else {
                                    hash ^= 59971671518510385;
                                }
                            } else {
                                hash ^= 63363867976485307;
                            }
                        } else {
                            hash ^= 70839269077936365;
                        }
                    } else if (flag[9] == 'C') {
                        hash ^= 40678497170322256;
                        printf("found %c at %d\n", 67, 9);
                        if (flag[62] == 'T') {
                            hash ^= 42683086405306083;
                            printf("found %c at %d\n", 84, 62);
                            if (flag[210] == 'R') {
                                hash ^= 47275151026163694;
                                printf("found %c at %d\n", 82, 210);
                                if (flag[89] == 'w') {
                                    hash ^= 63053889479102308;
                                    printf("found %c at %d\n", 119, 89);
                                    if (flag[59] == 'S') {
                                        hash ^= 58671198440562568;
                                        printf("found %c at %d\n", 83, 59);
                                        if (flag[81] == 'v') {
                                            hash ^= 57248086744393695;
                                            printf("found %c at %d\n", 118, 81);
                                        } else if (flag[163] == 'R') {
                                            hash ^= 39814557959550184;
                                            printf("found %c at %d\n", 82, 163);
                                        } else {
                                            hash ^= 55927437385363965;
                                        }
                                    } else if (flag[12] == 'H') {
                                        hash ^= 66450135592300056;
                                        printf("found %c at %d\n", 72, 12);
                                        if (flag[119] == 'J') {
                                            hash ^= 51282193274290349;
                                            printf("found %c at %d\n", 74, 119);
                                        } else if (flag[70] == 'f') {
                                            hash ^= 66577874188547446;
                                            printf("found %c at %d\n", 102, 70);
                                        } else {
                                            hash ^= 45306967520738086;
                                        }
                                    } else {
                                        hash ^= 42156803816337321;
                                    }
                                } else if (flag[225] == 'B') {
                                    hash ^= 51735686886283949;
                                    printf("found %c at %d\n", 66, 225);
                                    if (flag[183] == 'b') {
                                        hash ^= 63691492242725569;
                                        printf("found %c at %d\n", 98, 183);
                                        if (flag[136] == 'h') {
                                            hash ^= 67821411258439329;
                                            printf("found %c at %d\n", 104, 136);
                                        } else if (flag[208] == 'r') {
                                            hash ^= 51926899907257401;
                                            printf("found %c at %d\n", 114, 208);
                                        } else {
                                            hash ^= 59425652199065970;
                                        }
                                    } else if (flag[13] == 'Z') {
                                        hash ^= 40708060228051542;
                                        printf("found %c at %d\n", 90, 13);
                                        if (flag[94] == 'k') {
                                            hash ^= 63744001645666793;
                                            printf("found %c at %d\n", 107, 94);
                                        } else if (flag[212] == 'M') {
                                            hash ^= 59168385819851457;
                                            printf("found %c at %d\n", 77, 212);
                                        } else {
                                            hash ^= 59307350430856342;
                                        }
                                    } else {
                                        hash ^= 55393918727535894;
                                    }
                                } else {
                                    hash ^= 36949894314812726;
                                }
                            } else if (flag[82] == 'B') {
                                hash ^= 44728192689720072;
                                printf("found %c at %d\n", 66, 82);
                                if (flag[61] == 'q') {
                                    hash ^= 71256867420159979;
                                    printf("found %c at %d\n", 113, 61);
                                    if (flag[227] == 'F') {
                                        hash ^= 52101007456731028;
                                        printf("found %c at %d\n", 70, 227);
                                        if (flag[171] == 'n') {
                                            hash ^= 38275371121606055;
                                            printf("found %c at %d\n", 110, 171);
                                        } else if (flag[34] == 'c') {
                                            hash ^= 62819525951579814;
                                            printf("found %c at %d\n", 99, 34);
                                        } else {
                                            hash ^= 69836964131755586;
                                        }
                                    } else if (flag[238] == 'J') {
                                        hash ^= 60076376797343660;
                                        printf("found %c at %d\n", 74, 238);
                                        if (flag[31] == 'F') {
                                            hash ^= 68792852297287151;
                                            printf("found %c at %d\n", 70, 31);
                                        } else if (flag[121] == 'j') {
                                            hash ^= 54444293726354080;
                                            printf("found %c at %d\n", 106, 121);
                                        } else {
                                            hash ^= 40677258388680313;
                                        }
                                    } else {
                                        hash ^= 43400296604040563;
                                    }
                                } else if (flag[41] == 's') {
                                    hash ^= 54433725835409386;
                                    printf("found %c at %d\n", 115, 41);
                                    if (flag[200] == '9') {
                                        hash ^= 53723730498049007;
                                        printf("found %c at %d\n", 57, 200);
                                        if (flag[255] == 'G') {
                                            hash ^= 64028699062331593;
                                            printf("found %c at %d\n", 71, 255);
                                        } else if (flag[158] == '7') {
                                            hash ^= 39361902929887947;
                                            printf("found %c at %d\n", 55, 158);
                                        } else {
                                            hash ^= 68144262271698219;
                                        }
                                    } else if (flag[216] == '0') {
                                        hash ^= 43120873861797580;
                                        printf("found %c at %d\n", 48, 216);
                                        if (flag[199] == '5') {
                                            hash ^= 70312067997957143;
                                            printf("found %c at %d\n", 53, 199);
                                        } else if (flag[255] == 'i') {
                                            hash ^= 59344563984940025;
                                            printf("found %c at %d\n", 105, 255);
                                        } else {
                                            hash ^= 67408869911682983;
                                        }
                                    } else {
                                        hash ^= 57068072354215797;
                                    }
                                } else {
                                    hash ^= 43598311701539413;
                                }
                            } else {
                                hash ^= 49766977060562922;
                            }
                        } else if (flag[8] == 'b') {
                            hash ^= 51496330144379570;
                            printf("found %c at %d\n", 98, 8);
                            if (flag[138] == 'N') {
                                hash ^= 63461746356766020;
                                printf("found %c at %d\n", 78, 138);
                                if (flag[172] == 'a') {
                                    hash ^= 52151562875396283;
                                    printf("found %c at %d\n", 97, 172);
                                    if (flag[65] == 'L') {
                                        hash ^= 43637009534409153;
                                        printf("found %c at %d\n", 76, 65);
                                        if (flag[20] == 'o') {
                                            hash ^= 59774781488646057;
                                            printf("found %c at %d\n", 111, 20);
                                        } else if (flag[171] == '7') {
                                            hash ^= 36832770579799557;
                                            printf("found %c at %d\n", 55, 171);
                                        } else {
                                            hash ^= 47091638590270712;
                                        }
                                    } else if (flag[185] == 'F') {
                                        hash ^= 69620698734847818;
                                        printf("found %c at %d\n", 70, 185);
                                        if (flag[157] == 'n') {
                                            hash ^= 68486501518739116;
                                            printf("found %c at %d\n", 110, 157);
                                        } else if (flag[144] == '}') {
                                            hash ^= 36598014380971179;
                                            printf("found %c at %d\n", 125, 144);
                                        } else {
                                            hash ^= 46305275205246163;
                                        }
                                    } else {
                                        hash ^= 56795696505414229;
                                    }
                                } else if (flag[246] == 'l') {
                                    hash ^= 47100327223724995;
                                    printf("found %c at %d\n", 108, 246);
                                    if (flag[150] == '7') {
                                        hash ^= 62111655519222727;
                                        printf("found %c at %d\n", 55, 150);
                                        if (flag[62] == 'o') {
                                            hash ^= 42190420059712818;
                                            printf("found %c at %d\n", 111, 62);
                                        } else if (flag[50] == 'w') {
                                            hash ^= 67938365813224942;
                                            printf("found %c at %d\n", 119, 50);
                                        } else {
                                            hash ^= 68781047431993068;
                                        }
                                    } else if (flag[18] == 'm') {
                                        hash ^= 49560598726509776;
                                        printf("found %c at %d\n", 109, 18);
                                        if (flag[95] == 'o') {
                                            hash ^= 38947468136698757;
                                            printf("found %c at %d\n", 111, 95);
                                        } else if (flag[119] == 'K') {
                                            hash ^= 47776944411808754;
                                            printf("found %c at %d\n", 75, 119);
                                        } else {
                                            hash ^= 47520570775729539;
                                        }
                                    } else {
                                        hash ^= 65991966133856860;
                                    }
                                } else {
                                    hash ^= 69113247402724054;
                                }
                            } else if (flag[2] == '6') {
                                hash ^= 66168246210961432;
                                printf("found %c at %d\n", 54, 2);
                                if (flag[7] == 'w') {
                                    hash ^= 46658646303510336;
                                    printf("found %c at %d\n", 119, 7);
                                    if (flag[243] == 'y') {
                                        hash ^= 71589314361376453;
                                        printf("found %c at %d\n", 121, 243);
                                        if (flag[15] == '3') {
                                            hash ^= 50004308843221523;
                                            printf("found %c at %d\n", 51, 15);
                                        } else if (flag[206] == 'f') {
                                            hash ^= 71174892494386127;
                                            printf("found %c at %d\n", 102, 206);
                                        } else {
                                            hash ^= 63221528752238628;
                                        }
                                    } else if (flag[6] == 'p') {
                                        hash ^= 66641846562644875;
                                        printf("found %c at %d\n", 112, 6);
                                        if (flag[91] == 'w') {
                                            hash ^= 41158470278959676;
                                            printf("found %c at %d\n", 119, 91);
                                        } else if (flag[4] == 'o') {
                                            hash ^= 69793241579792749;
                                            printf("found %c at %d\n", 111, 4);
                                        } else {
                                            hash ^= 51460792017841295;
                                        }
                                    } else {
                                        hash ^= 70125226046967124;
                                    }
                                } else if (flag[75] == 'D') {
                                    hash ^= 39489474174479997;
                                    printf("found %c at %d\n", 68, 75);
                                    if (flag[61] == 'B') {
                                        hash ^= 53652852887630063;
                                        printf("found %c at %d\n", 66, 61);
                                        if (flag[79] == 'R') {
                                            hash ^= 54080592719821483;
                                            printf("found %c at %d\n", 82, 79);
                                        } else if (flag[16] == 'U') {
                                            hash ^= 39536504489073045;
                                            printf("found %c at %d\n", 85, 16);
                                        } else {
                                            hash ^= 46251646190738029;
                                        }
                                    } else if (flag[253] == 'p') {
                                        hash ^= 66258660835945679;
                                        printf("found %c at %d\n", 112, 253);
                                        if (flag[56] == 'x') {
                                            hash ^= 69417777937011116;
                                            printf("found %c at %d\n", 120, 56);
                                        } else if (flag[104] == 'A') {
                                            hash ^= 65504209112791144;
                                            printf("found %c at %d\n", 65, 104);
                                        } else {
                                            hash ^= 66430213629519472;
                                        }
                                    } else {
                                        hash ^= 54404688720684365;
                                    }
                                } else {
                                    hash ^= 71900636710053775;
                                }
                            } else {
                                hash ^= 44814407050986578;
                            }
                        } else {
                            hash ^= 54655224726044742;
                        }
                    } else {
                        hash ^= 41223960405702801;
                    }
                } else if (flag[9] == 'G') {
                    hash ^= 60600775315573225;
                    printf("found %c at %d\n", 71, 9);
                    if (flag[119] == 'e') {
                        hash ^= 52970646749919163;
                        printf("found %c at %d\n", 101, 119);
                        if (flag[189] == 'U') {
                            hash ^= 59016551214705672;
                            printf("found %c at %d\n", 85, 189);
                            if (flag[110] == 'E') {
                                hash ^= 45019573659270996;
                                printf("found %c at %d\n", 69, 110);
                                if (flag[154] == 'V') {
                                    hash ^= 70591805044237342;
                                    printf("found %c at %d\n", 86, 154);
                                    if (flag[226] == 'l') {
                                        hash ^= 69071068946402439;
                                        printf("found %c at %d\n", 108, 226);
                                        if (flag[115] == 'G') {
                                            hash ^= 68056170280183642;
                                            printf("found %c at %d\n", 71, 115);
                                        } else if (flag[59] == 'E') {
                                            hash ^= 63908090865546588;
                                            printf("found %c at %d\n", 69, 59);
                                        } else {
                                            hash ^= 67895635890864534;
                                        }
                                    } else if (flag[126] == 'j') {
                                        hash ^= 51353969688951340;
                                        printf("found %c at %d\n", 106, 126);
                                        if (flag[127] == 'F') {
                                            hash ^= 45903266761040316;
                                            printf("found %c at %d\n", 70, 127);
                                        } else if (flag[245] == 'z') {
                                            hash ^= 40956683566917391;
                                            printf("found %c at %d\n", 122, 245);
                                        } else {
                                            hash ^= 50555638527223600;
                                        }
                                    } else {
                                        hash ^= 59140483084555507;
                                    }
                                } else if (flag[80] == '0') {
                                    hash ^= 64927584627968467;
                                    printf("found %c at %d\n", 48, 80);
                                    if (flag[147] == '6') {
                                        hash ^= 60817637891018510;
                                        printf("found %c at %d\n", 54, 147);
                                        if (flag[50] == 'w') {
                                            hash ^= 41880771940419730;
                                            printf("found %c at %d\n", 119, 50);
                                        } else if (flag[140] == 'e') {
                                            hash ^= 65421394058697413;
                                            printf("found %c at %d\n", 101, 140);
                                        } else {
                                            hash ^= 62594936956362133;
                                        }
                                    } else if (flag[142] == 'J') {
                                        hash ^= 68785255561786562;
                                        printf("found %c at %d\n", 74, 142);
                                        if (flag[215] == '{') {
                                            hash ^= 50311875594070221;
                                            printf("found %c at %d\n", 123, 215);
                                        } else if (flag[251] == 'r') {
                                            hash ^= 48674674021714405;
                                            printf("found %c at %d\n", 114, 251);
                                        } else {
                                            hash ^= 68038221355859365;
                                        }
                                    } else {
                                        hash ^= 36115526896405358;
                                    }
                                } else {
                                    hash ^= 36495120852999116;
                                }
                            } else if (flag[94] == 'N') {
                                hash ^= 40986342800547144;
                                printf("found %c at %d\n", 78, 94);
                                if (flag[72] == 'e') {
                                    hash ^= 50577216968600248;
                                    printf("found %c at %d\n", 101, 72);
                                    if (flag[124] == 'K') {
                                        hash ^= 51624850688874860;
                                        printf("found %c at %d\n", 75, 124);
                                        if (flag[9] == 'j') {
                                            hash ^= 71216629639113324;
                                            printf("found %c at %d\n", 106, 9);
                                        } else if (flag[97] == 'Z') {
                                            hash ^= 65241607117194267;
                                            printf("found %c at %d\n", 90, 97);
                                        } else {
                                            hash ^= 58816270436560592;
                                        }
                                    } else if (flag[13] == 'b') {
                                        hash ^= 41292781291216150;
                                        printf("found %c at %d\n", 98, 13);
                                        if (flag[48] == 'F') {
                                            hash ^= 54580369801103506;
                                            printf("found %c at %d\n", 70, 48);
                                        } else if (flag[32] == 'p') {
                                            hash ^= 45137591854464962;
                                            printf("found %c at %d\n", 112, 32);
                                        } else {
                                            hash ^= 44101461182357408;
                                        }
                                    } else {
                                        hash ^= 53874058941318484;
                                    }
                                } else if (flag[147] == '4') {
                                    hash ^= 54573354056528581;
                                    printf("found %c at %d\n", 52, 147);
                                    if (flag[75] == 'a') {
                                        hash ^= 58649025861001465;
                                        printf("found %c at %d\n", 97, 75);
                                        if (flag[80] == 'h') {
                                            hash ^= 54776964431455942;
                                            printf("found %c at %d\n", 104, 80);
                                        } else if (flag[85] == 'B') {
                                            hash ^= 52160812465098481;
                                            printf("found %c at %d\n", 66, 85);
                                        } else {
                                            hash ^= 46531401919061374;
                                        }
                                    } else if (flag[189] == 'n') {
                                        hash ^= 42318869315951559;
                                        printf("found %c at %d\n", 110, 189);
                                        if (flag[109] == '8') {
                                            hash ^= 66337088635511905;
                                            printf("found %c at %d\n", 56, 109);
                                        } else if (flag[169] == '_') {
                                            hash ^= 60936774771098819;
                                            printf("found %c at %d\n", 95, 169);
                                        } else {
                                            hash ^= 55365858571989926;
                                        }
                                    } else {
                                        hash ^= 56386424735749056;
                                    }
                                } else {
                                    hash ^= 60850704402437179;
                                }
                            } else {
                                hash ^= 56088573091446480;
                            }
                        } else if (flag[209] == 'N') {
                            hash ^= 62341402943649058;
                            printf("found %c at %d\n", 78, 209);
                            if (flag[39] == 'B') {
                                hash ^= 56259828749429562;
                                printf("found %c at %d\n", 66, 39);
                                if (flag[17] == 'P') {
                                    hash ^= 53501976873947465;
                                    printf("found %c at %d\n", 80, 17);
                                    if (flag[100] == 'K') {
                                        hash ^= 69643553286867835;
                                        printf("found %c at %d\n", 75, 100);
                                        if (flag[250] == 'P') {
                                            hash ^= 42313131679603748;
                                            printf("found %c at %d\n", 80, 250);
                                        } else if (flag[15] == 'f') {
                                            hash ^= 66754128477735593;
                                            printf("found %c at %d\n", 102, 15);
                                        } else {
                                            hash ^= 49659615290016230;
                                        }
                                    } else if (flag[72] == 'u') {
                                        hash ^= 36066000029556511;
                                        printf("found %c at %d\n", 117, 72);
                                        if (flag[149] == 'l') {
                                            hash ^= 62948177607096080;
                                            printf("found %c at %d\n", 108, 149);
                                        } else if (flag[112] == 'P') {
                                            hash ^= 59257336377321612;
                                            printf("found %c at %d\n", 80, 112);
                                        } else {
                                            hash ^= 52378582854715148;
                                        }
                                    } else {
                                        hash ^= 36282340911108024;
                                    }
                                } else if (flag[17] == 'C') {
                                    hash ^= 63462446413955795;
                                    printf("found %c at %d\n", 67, 17);
                                    if (flag[103] == '}') {
                                        hash ^= 71135983610910113;
                                        printf("found %c at %d\n", 125, 103);
                                        if (flag[117] == 'k') {
                                            hash ^= 63628531398088383;
                                            printf("found %c at %d\n", 107, 117);
                                        } else if (flag[248] == 'r') {
                                            hash ^= 43277735481929605;
                                            printf("found %c at %d\n", 114, 248);
                                        } else {
                                            hash ^= 39209646486427816;
                                        }
                                    } else if (flag[119] == '9') {
                                        hash ^= 50709210527998663;
                                        printf("found %c at %d\n", 57, 119);
                                        if (flag[83] == 'w') {
                                            hash ^= 56854637082011405;
                                            printf("found %c at %d\n", 119, 83);
                                        } else if (flag[241] == '_') {
                                            hash ^= 46652435778476787;
                                            printf("found %c at %d\n", 95, 241);
                                        } else {
                                            hash ^= 39590733761738547;
                                        }
                                    } else {
                                        hash ^= 69374750516670145;
                                    }
                                } else {
                                    hash ^= 69580538570682717;
                                }
                            } else if (flag[97] == 'd') {
                                hash ^= 42602400890512444;
                                printf("found %c at %d\n", 100, 97);
                                if (flag[205] == 'Q') {
                                    hash ^= 66622098197368650;
                                    printf("found %c at %d\n", 81, 205);
                                    if (flag[235] == 'c') {
                                        hash ^= 56847621725249390;
                                        printf("found %c at %d\n", 99, 235);
                                        if (flag[8] == 'R') {
                                            hash ^= 44386338927487204;
                                            printf("found %c at %d\n", 82, 8);
                                        } else if (flag[104] == 't') {
                                            hash ^= 69154245950848526;
                                            printf("found %c at %d\n", 116, 104);
                                        } else {
                                            hash ^= 38240064275141143;
                                        }
                                    } else if (flag[150] == 'f') {
                                        hash ^= 67997234482490705;
                                        printf("found %c at %d\n", 102, 150);
                                        if (flag[28] == 'r') {
                                            hash ^= 44261012217331839;
                                            printf("found %c at %d\n", 114, 28);
                                        } else if (flag[119] == '_') {
                                            hash ^= 61606955285213516;
                                            printf("found %c at %d\n", 95, 119);
                                        } else {
                                            hash ^= 58899449849160488;
                                        }
                                    } else {
                                        hash ^= 40884090739265289;
                                    }
                                } else if (flag[134] == 'b') {
                                    hash ^= 53463046246712072;
                                    printf("found %c at %d\n", 98, 134);
                                    if (flag[27] == 'F') {
                                        hash ^= 45679857243507802;
                                        printf("found %c at %d\n", 70, 27);
                                        if (flag[4] == 'g') {
                                            hash ^= 71610498904480870;
                                            printf("found %c at %d\n", 103, 4);
                                        } else if (flag[252] == 'L') {
                                            hash ^= 40532996978329937;
                                            printf("found %c at %d\n", 76, 252);
                                        } else {
                                            hash ^= 54323283061019246;
                                        }
                                    } else if (flag[101] == 'r') {
                                        hash ^= 42726047498721882;
                                        printf("found %c at %d\n", 114, 101);
                                        if (flag[80] == 'q') {
                                            hash ^= 51246499818613266;
                                            printf("found %c at %d\n", 113, 80);
                                        } else if (flag[82] == '3') {
                                            hash ^= 55282264241198871;
                                            printf("found %c at %d\n", 51, 82);
                                        } else {
                                            hash ^= 43485006100338403;
                                        }
                                    } else {
                                        hash ^= 48262894478263731;
                                    }
                                } else {
                                    hash ^= 68021032256971629;
                                }
                            } else {
                                hash ^= 42638736046473879;
                            }
                        } else {
                            hash ^= 65972580641072875;
                        }
                    } else if (flag[238] == 'h') {
                        hash ^= 41378732967810868;
                        printf("found %c at %d\n", 104, 238);
                        if (flag[119] == '9') {
                            hash ^= 56839812518125365;
                            printf("found %c at %d\n", 57, 119);
                            if (flag[113] == '1') {
                                hash ^= 65266012886549736;
                                printf("found %c at %d\n", 49, 113);
                                if (flag[246] == 'j') {
                                    hash ^= 42041977637391902;
                                    printf("found %c at %d\n", 106, 246);
                                    if (flag[106] == 'W') {
                                        hash ^= 45326880290726309;
                                        printf("found %c at %d\n", 87, 106);
                                        if (flag[186] == 'N') {
                                            hash ^= 63747271464738252;
                                            printf("found %c at %d\n", 78, 186);
                                        } else if (flag[73] == 'k') {
                                            hash ^= 57910228446816731;
                                            printf("found %c at %d\n", 107, 73);
                                        } else {
                                            hash ^= 55588114696220543;
                                        }
                                    } else if (flag[29] == 's') {
                                        hash ^= 70173693343814014;
                                        printf("found %c at %d\n", 115, 29);
                                        if (flag[8] == 'U') {
                                            hash ^= 52229139179489679;
                                            printf("found %c at %d\n", 85, 8);
                                        } else if (flag[79] == '7') {
                                            hash ^= 37316289920052282;
                                            printf("found %c at %d\n", 55, 79);
                                        } else {
                                            hash ^= 57293726386918692;
                                        }
                                    } else {
                                        hash ^= 39861141001510039;
                                    }
                                } else if (flag[244] == 'W') {
                                    hash ^= 50799172241449038;
                                    printf("found %c at %d\n", 87, 244);
                                    if (flag[103] == 'K') {
                                        hash ^= 46585163795463018;
                                        printf("found %c at %d\n", 75, 103);
                                        if (flag[20] == 'I') {
                                            hash ^= 43297464572493223;
                                            printf("found %c at %d\n", 73, 20);
                                        } else if (flag[234] == '}') {
                                            hash ^= 70959478894936591;
                                            printf("found %c at %d\n", 125, 234);
                                        } else {
                                            hash ^= 37908855682171869;
                                        }
                                    } else if (flag[21] == 'H') {
                                        hash ^= 63511044690902206;
                                        printf("found %c at %d\n", 72, 21);
                                        if (flag[251] == '7') {
                                            hash ^= 58326736982280450;
                                            printf("found %c at %d\n", 55, 251);
                                        } else if (flag[24] == 'I') {
                                            hash ^= 71912127387383086;
                                            printf("found %c at %d\n", 73, 24);
                                        } else {
                                            hash ^= 40698920946824375;
                                        }
                                    } else {
                                        hash ^= 57774824439892059;
                                    }
                                } else {
                                    hash ^= 63240588803527261;
                                }
                            } else if (flag[79] == 'O') {
                                hash ^= 62484016560115160;
                                printf("found %c at %d\n", 79, 79);
                                if (flag[199] == 'V') {
                                    hash ^= 60296361140638254;
                                    printf("found %c at %d\n", 86, 199);
                                    if (flag[144] == 'B') {
                                        hash ^= 48883374874842052;
                                        printf("found %c at %d\n", 66, 144);
                                        if (flag[149] == '4') {
                                            hash ^= 57383282362143872;
                                            printf("found %c at %d\n", 52, 149);
                                        } else if (flag[30] == 'p') {
                                            hash ^= 44308226091079553;
                                            printf("found %c at %d\n", 112, 30);
                                        } else {
                                            hash ^= 67086522961328548;
                                        }
                                    } else if (flag[234] == '_') {
                                        hash ^= 63780383682425882;
                                        printf("found %c at %d\n", 95, 234);
                                        if (flag[105] == 'r') {
                                            hash ^= 49503086136858254;
                                            printf("found %c at %d\n", 114, 105);
                                        } else if (flag[205] == 'p') {
                                            hash ^= 51680269422460198;
                                            printf("found %c at %d\n", 112, 205);
                                        } else {
                                            hash ^= 53270631549973655;
                                        }
                                    } else {
                                        hash ^= 58950689342405343;
                                    }
                                } else if (flag[247] == 'K') {
                                    hash ^= 71362383912358754;
                                    printf("found %c at %d\n", 75, 247);
                                    if (flag[223] == 'c') {
                                        hash ^= 62867286429486816;
                                        printf("found %c at %d\n", 99, 223);
                                        if (flag[152] == '7') {
                                            hash ^= 47737370506751832;
                                            printf("found %c at %d\n", 55, 152);
                                        } else if (flag[7] == 'n') {
                                            hash ^= 67797514684533704;
                                            printf("found %c at %d\n", 110, 7);
                                        } else {
                                            hash ^= 64623221267868537;
                                        }
                                    } else if (flag[117] == 'T') {
                                        hash ^= 36372858483204299;
                                        printf("found %c at %d\n", 84, 117);
                                        if (flag[224] == 'Q') {
                                            hash ^= 70886833206223702;
                                            printf("found %c at %d\n", 81, 224);
                                        } else if (flag[223] == 'd') {
                                            hash ^= 41842005825890539;
                                            printf("found %c at %d\n", 100, 223);
                                        } else {
                                            hash ^= 62710666313551527;
                                        }
                                    } else {
                                        hash ^= 44881486573338948;
                                    }
                                } else {
                                    hash ^= 68889927606554733;
                                }
                            } else {
                                hash ^= 53128062488854241;
                            }
                        } else if (flag[20] == 'X') {
                            hash ^= 38484193039634463;
                            printf("found %c at %d\n", 88, 20);
                            if (flag[149] == 'c') {
                                hash ^= 68204305417668215;
                                printf("found %c at %d\n", 99, 149);
                                if (flag[170] == '{') {
                                    hash ^= 69923426278281745;
                                    printf("found %c at %d\n", 123, 170);
                                    if (flag[228] == 'x') {
                                        hash ^= 64260035165800996;
                                        printf("found %c at %d\n", 120, 228);
                                        if (flag[147] == 'l') {
                                            hash ^= 46121622373675300;
                                            printf("found %c at %d\n", 108, 147);
                                        } else if (flag[213] == 'K') {
                                            hash ^= 54307478492329634;
                                            printf("found %c at %d\n", 75, 213);
                                        } else {
                                            hash ^= 46497706753772039;
                                        }
                                    } else if (flag[99] == 'R') {
                                        hash ^= 71556896994926772;
                                        printf("found %c at %d\n", 82, 99);
                                        if (flag[203] == 'M') {
                                            hash ^= 49897858874791829;
                                            printf("found %c at %d\n", 77, 203);
                                        } else if (flag[83] == '1') {
                                            hash ^= 36801453751139825;
                                            printf("found %c at %d\n", 49, 83);
                                        } else {
                                            hash ^= 64172160259637211;
                                        }
                                    } else {
                                        hash ^= 71242996199981202;
                                    }
                                } else if (flag[110] == 'Q') {
                                    hash ^= 45527041482634238;
                                    printf("found %c at %d\n", 81, 110);
                                    if (flag[220] == '4') {
                                        hash ^= 59802155257185820;
                                        printf("found %c at %d\n", 52, 220);
                                        if (flag[121] == 'B') {
                                            hash ^= 62089832632984436;
                                            printf("found %c at %d\n", 66, 121);
                                        } else if (flag[113] == '8') {
                                            hash ^= 60302715568881617;
                                            printf("found %c at %d\n", 56, 113);
                                        } else {
                                            hash ^= 65529486027844384;
                                        }
                                    } else if (flag[150] == 'Q') {
                                        hash ^= 47824100614018441;
                                        printf("found %c at %d\n", 81, 150);
                                        if (flag[178] == 'J') {
                                            hash ^= 49874901786761285;
                                            printf("found %c at %d\n", 74, 178);
                                        } else if (flag[205] == 'C') {
                                            hash ^= 46666720685534920;
                                            printf("found %c at %d\n", 67, 205);
                                        } else {
                                            hash ^= 61229843089439870;
                                        }
                                    } else {
                                        hash ^= 49334097041882617;
                                    }
                                } else {
                                    hash ^= 63069575314196054;
                                }
                            } else if (flag[239] == 'S') {
                                hash ^= 59568514529016812;
                                printf("found %c at %d\n", 83, 239);
                                if (flag[1] == 'n') {
                                    hash ^= 46000519216374529;
                                    printf("found %c at %d\n", 110, 1);
                                    if (flag[109] == '_') {
                                        hash ^= 55102939157054588;
                                        printf("found %c at %d\n", 95, 109);
                                        if (flag[200] == 'S') {
                                            hash ^= 50411659506620392;
                                            printf("found %c at %d\n", 83, 200);
                                        } else if (flag[53] == 'L') {
                                            hash ^= 45391988738196485;
                                            printf("found %c at %d\n", 76, 53);
                                        } else {
                                            hash ^= 44754538431403805;
                                        }
                                    } else if (flag[83] == 'g') {
                                        hash ^= 42196247899035586;
                                        printf("found %c at %d\n", 103, 83);
                                        if (flag[63] == '3') {
                                            hash ^= 64015153432804857;
                                            printf("found %c at %d\n", 51, 63);
                                        } else if (flag[10] == 'i') {
                                            hash ^= 49238826680795675;
                                            printf("found %c at %d\n", 105, 10);
                                        } else {
                                            hash ^= 52820438456668871;
                                        }
                                    } else {
                                        hash ^= 52309772096504386;
                                    }
                                } else if (flag[161] == 'n') {
                                    hash ^= 69901701193066722;
                                    printf("found %c at %d\n", 110, 161);
                                    if (flag[105] == 'c') {
                                        hash ^= 63083091795622797;
                                        printf("found %c at %d\n", 99, 105);
                                        if (flag[144] == 'w') {
                                            hash ^= 46387788022368888;
                                            printf("found %c at %d\n", 119, 144);
                                        } else if (flag[249] == 'a') {
                                            hash ^= 46354261050492578;
                                            printf("found %c at %d\n", 97, 249);
                                        } else {
                                            hash ^= 58316186286611076;
                                        }
                                    } else if (flag[91] == 'B') {
                                        hash ^= 48768763554198616;
                                        printf("found %c at %d\n", 66, 91);
                                        if (flag[111] == 'A') {
                                            hash ^= 57994052786707361;
                                            printf("found %c at %d\n", 65, 111);
                                        } else if (flag[83] == 'c') {
                                            hash ^= 52061198232934340;
                                            printf("found %c at %d\n", 99, 83);
                                        } else {
                                            hash ^= 37807623858928877;
                                        }
                                    } else {
                                        hash ^= 66585240099462507;
                                    }
                                } else {
                                    hash ^= 56864580473457414;
                                }
                            } else {
                                hash ^= 42644277152606109;
                            }
                        } else {
                            hash ^= 59222126440890492;
                        }
                    } else {
                        hash ^= 44621625933072777;
                    }
                } else {
                    hash ^= 49867654130983364;
                }
            } else if (flag[120] == '7') {
                hash ^= 49807320808627480;
                printf("found %c at %d\n", 55, 120);
                if (flag[29] == '}') {
                    hash ^= 52146919701957703;
                    printf("found %c at %d\n", 125, 29);
                    if (flag[74] == 'F') {
                        hash ^= 67011843041387001;
                        printf("found %c at %d\n", 70, 74);
                        if (flag[91] == '0') {
                            hash ^= 45172062167063598;
                            printf("found %c at %d\n", 48, 91);
                            if (flag[242] == 'k') {
                                hash ^= 40722218046634456;
                                printf("found %c at %d\n", 107, 242);
                                if (flag[123] == '5') {
                                    hash ^= 45773234484021522;
                                    printf("found %c at %d\n", 53, 123);
                                    if (flag[110] == 'a') {
                                        hash ^= 46594285691536689;
                                        printf("found %c at %d\n", 97, 110);
                                        if (flag[19] == 'y') {
                                            hash ^= 67418111575146652;
                                            printf("found %c at %d\n", 121, 19);
                                        } else if (flag[224] == '7') {
                                            hash ^= 67660700760119771;
                                            printf("found %c at %d\n", 55, 224);
                                        } else {
                                            hash ^= 37020567383333108;
                                        }
                                    } else if (flag[49] == 'r') {
                                        hash ^= 48450680113006203;
                                        printf("found %c at %d\n", 114, 49);
                                        if (flag[203] == 'n') {
                                            hash ^= 46999664431637711;
                                            printf("found %c at %d\n", 110, 203);
                                        } else if (flag[43] == 'Y') {
                                            hash ^= 50779446371380818;
                                            printf("found %c at %d\n", 89, 43);
                                        } else {
                                            hash ^= 45938498134975027;
                                        }
                                    } else {
                                        hash ^= 63462002469280082;
                                    }
                                } else if (flag[214] == 'k') {
                                    hash ^= 59029140921411401;
                                    printf("found %c at %d\n", 107, 214);
                                    if (flag[20] == 'C') {
                                        hash ^= 70492142058688082;
                                        printf("found %c at %d\n", 67, 20);
                                        if (flag[86] == '3') {
                                            hash ^= 58956211477043933;
                                            printf("found %c at %d\n", 51, 86);
                                        } else if (flag[172] == 'k') {
                                            hash ^= 41898138126254837;
                                            printf("found %c at %d\n", 107, 172);
                                        } else {
                                            hash ^= 67458485630606391;
                                        }
                                    } else if (flag[198] == 'j') {
                                        hash ^= 40683968251367649;
                                        printf("found %c at %d\n", 106, 198);
                                        if (flag[100] == '7') {
                                            hash ^= 37035810526209946;
                                            printf("found %c at %d\n", 55, 100);
                                        } else if (flag[175] == 'E') {
                                            hash ^= 67642311651966318;
                                            printf("found %c at %d\n", 69, 175);
                                        } else {
                                            hash ^= 37583647195427532;
                                        }
                                    } else {
                                        hash ^= 52104718754713563;
                                    }
                                } else {
                                    hash ^= 58010935022118800;
                                }
                            } else if (flag[33] == 'h') {
                                hash ^= 61162344291364769;
                                printf("found %c at %d\n", 104, 33);
                                if (flag[111] == 'G') {
                                    hash ^= 58734178426425475;
                                    printf("found %c at %d\n", 71, 111);
                                    if (flag[73] == '{') {
                                        hash ^= 44541115549434003;
                                        printf("found %c at %d\n", 123, 73);
                                        if (flag[150] == 'n') {
                                            hash ^= 37289881461492086;
                                            printf("found %c at %d\n", 110, 150);
                                        } else if (flag[218] == 't') {
                                            hash ^= 61995239807743891;
                                            printf("found %c at %d\n", 116, 218);
                                        } else {
                                            hash ^= 38679838716631388;
                                        }
                                    } else if (flag[176] == 'V') {
                                        hash ^= 68075936042020257;
                                        printf("found %c at %d\n", 86, 176);
                                        if (flag[36] == 'T') {
                                            hash ^= 49541747413785362;
                                            printf("found %c at %d\n", 84, 36);
                                        } else if (flag[51] == 's') {
                                            hash ^= 38939147300583731;
                                            printf("found %c at %d\n", 115, 51);
                                        } else {
                                            hash ^= 37999006392427633;
                                        }
                                    } else {
                                        hash ^= 42807839410045433;
                                    }
                                } else if (flag[45] == '7') {
                                    hash ^= 69432279341480724;
                                    printf("found %c at %d\n", 55, 45);
                                    if (flag[233] == 'd') {
                                        hash ^= 67274533706658075;
                                        printf("found %c at %d\n", 100, 233);
                                        if (flag[209] == 'U') {
                                            hash ^= 65660316492460179;
                                            printf("found %c at %d\n", 85, 209);
                                        } else if (flag[8] == 'E') {
                                            hash ^= 71867072856883479;
                                            printf("found %c at %d\n", 69, 8);
                                        } else {
                                            hash ^= 57694962086719556;
                                        }
                                    } else if (flag[124] == 'J') {
                                        hash ^= 41190134793792248;
                                        printf("found %c at %d\n", 74, 124);
                                        if (flag[65] == 'C') {
                                            hash ^= 68322043820988142;
                                            printf("found %c at %d\n", 67, 65);
                                        } else if (flag[242] == 'i') {
                                            hash ^= 61857799655504221;
                                            printf("found %c at %d\n", 105, 242);
                                        } else {
                                            hash ^= 50896488379859606;
                                        }
                                    } else {
                                        hash ^= 42738779303705547;
                                    }
                                } else {
                                    hash ^= 71471588044711100;
                                }
                            } else {
                                hash ^= 57334767353990168;
                            }
                        } else if (flag[230] == 'Q') {
                            hash ^= 64182571421805284;
                            printf("found %c at %d\n", 81, 230);
                            if (flag[199] == 'p') {
                                hash ^= 69165765248253953;
                                printf("found %c at %d\n", 112, 199);
                                if (flag[53] == '7') {
                                    hash ^= 49455633261387649;
                                    printf("found %c at %d\n", 55, 53);
                                    if (flag[255] == 'a') {
                                        hash ^= 40263343465498738;
                                        printf("found %c at %d\n", 97, 255);
                                        if (flag[51] == 'G') {
                                            hash ^= 62667795954808304;
                                            printf("found %c at %d\n", 71, 51);
                                        } else if (flag[216] == 'x') {
                                            hash ^= 37649220112176194;
                                            printf("found %c at %d\n", 120, 216);
                                        } else {
                                            hash ^= 48161068529188803;
                                        }
                                    } else if (flag[28] == 'A') {
                                        hash ^= 49796054415412641;
                                        printf("found %c at %d\n", 65, 28);
                                        if (flag[8] == 'R') {
                                            hash ^= 68566081420449573;
                                            printf("found %c at %d\n", 82, 8);
                                        } else if (flag[127] == 'F') {
                                            hash ^= 66760359425624321;
                                            printf("found %c at %d\n", 70, 127);
                                        } else {
                                            hash ^= 54694611219436261;
                                        }
                                    } else {
                                        hash ^= 52180050521231065;
                                    }
                                } else if (flag[131] == 'Z') {
                                    hash ^= 69173193025881161;
                                    printf("found %c at %d\n", 90, 131);
                                    if (flag[182] == '5') {
                                        hash ^= 62286798264005301;
                                        printf("found %c at %d\n", 53, 182);
                                        if (flag[67] == '_') {
                                            hash ^= 51567969437584412;
                                            printf("found %c at %d\n", 95, 67);
                                        } else if (flag[99] == 'd') {
                                            hash ^= 42859367438023779;
                                            printf("found %c at %d\n", 100, 99);
                                        } else {
                                            hash ^= 61504243235031256;
                                        }
                                    } else if (flag[66] == 'T') {
                                        hash ^= 62219440221135757;
                                        printf("found %c at %d\n", 84, 66);
                                        if (flag[75] == 'd') {
                                            hash ^= 38841436132493605;
                                            printf("found %c at %d\n", 100, 75);
                                        } else if (flag[196] == 'L') {
                                            hash ^= 59375041263109578;
                                            printf("found %c at %d\n", 76, 196);
                                        } else {
                                            hash ^= 55748637996426547;
                                        }
                                    } else {
                                        hash ^= 64398546318232728;
                                    }
                                } else {
                                    hash ^= 44775276091331832;
                                }
                            } else if (flag[93] == 'j') {
                                hash ^= 63210760182697442;
                                printf("found %c at %d\n", 106, 93);
                                if (flag[46] == 'K') {
                                    hash ^= 42568554220650663;
                                    printf("found %c at %d\n", 75, 46);
                                    if (flag[176] == 'N') {
                                        hash ^= 57799048746407630;
                                        printf("found %c at %d\n", 78, 176);
                                        if (flag[229] == 'Q') {
                                            hash ^= 51222472665466891;
                                            printf("found %c at %d\n", 81, 229);
                                        } else if (flag[221] == 'N') {
                                            hash ^= 66020928106433733;
                                            printf("found %c at %d\n", 78, 221);
                                        } else {
                                            hash ^= 37228676528673632;
                                        }
                                    } else if (flag[145] == 't') {
                                        hash ^= 69241222179847061;
                                        printf("found %c at %d\n", 116, 145);
                                        if (flag[134] == '4') {
                                            hash ^= 49153648543351458;
                                            printf("found %c at %d\n", 52, 134);
                                        } else if (flag[156] == '5') {
                                            hash ^= 69653213981404971;
                                            printf("found %c at %d\n", 53, 156);
                                        } else {
                                            hash ^= 60383682948923113;
                                        }
                                    } else {
                                        hash ^= 52393352204419463;
                                    }
                                } else if (flag[255] == 'S') {
                                    hash ^= 57749691391446927;
                                    printf("found %c at %d\n", 83, 255);
                                    if (flag[203] == 'k') {
                                        hash ^= 49741255682734930;
                                        printf("found %c at %d\n", 107, 203);
                                        if (flag[131] == 'd') {
                                            hash ^= 54782183713250862;
                                            printf("found %c at %d\n", 100, 131);
                                        } else if (flag[177] == 'o') {
                                            hash ^= 55406371647709857;
                                            printf("found %c at %d\n", 111, 177);
                                        } else {
                                            hash ^= 44335649331458636;
                                        }
                                    } else if (flag[185] == 'a') {
                                        hash ^= 65085258138466281;
                                        printf("found %c at %d\n", 97, 185);
                                        if (flag[158] == 'W') {
                                            hash ^= 53381094969694466;
                                            printf("found %c at %d\n", 87, 158);
                                        } else if (flag[106] == 's') {
                                            hash ^= 61880454322714583;
                                            printf("found %c at %d\n", 115, 106);
                                        } else {
                                            hash ^= 48133206432857794;
                                        }
                                    } else {
                                        hash ^= 48362452843561077;
                                    }
                                } else {
                                    hash ^= 62741917269680903;
                                }
                            } else {
                                hash ^= 47782569216225538;
                            }
                        } else {
                            hash ^= 69434593264253183;
                        }
                    } else if (flag[154] == 'w') {
                        hash ^= 45162907145883567;
                        printf("found %c at %d\n", 119, 154);
                        if (flag[234] == 'g') {
                            hash ^= 68052700872710491;
                            printf("found %c at %d\n", 103, 234);
                            if (flag[249] == 'Y') {
                                hash ^= 42471448501067053;
                                printf("found %c at %d\n", 89, 249);
                                if (flag[206] == 'd') {
                                    hash ^= 70814507909630181;
                                    printf("found %c at %d\n", 100, 206);
                                    if (flag[229] == 'A') {
                                        hash ^= 46968475462459845;
                                        printf("found %c at %d\n", 65, 229);
                                        if (flag[22] == '}') {
                                            hash ^= 65023748557614640;
                                            printf("found %c at %d\n", 125, 22);
                                        } else if (flag[211] == '1') {
                                            hash ^= 54940297391812466;
                                            printf("found %c at %d\n", 49, 211);
                                        } else {
                                            hash ^= 56450511908458553;
                                        }
                                    } else if (flag[21] == 'v') {
                                        hash ^= 59106453852450004;
                                        printf("found %c at %d\n", 118, 21);
                                        if (flag[195] == 't') {
                                            hash ^= 54534317025678553;
                                            printf("found %c at %d\n", 116, 195);
                                        } else if (flag[40] == 'I') {
                                            hash ^= 45465580295622231;
                                            printf("found %c at %d\n", 73, 40);
                                        } else {
                                            hash ^= 38597077046740366;
                                        }
                                    } else {
                                        hash ^= 52061204842350409;
                                    }
                                } else if (flag[57] == 'k') {
                                    hash ^= 53338486038492215;
                                    printf("found %c at %d\n", 107, 57);
                                    if (flag[148] == 'I') {
                                        hash ^= 49106817610531603;
                                        printf("found %c at %d\n", 73, 148);
                                        if (flag[225] == 'f') {
                                            hash ^= 63668241328879871;
                                            printf("found %c at %d\n", 102, 225);
                                        } else if (flag[241] == 'e') {
                                            hash ^= 64443429818883110;
                                            printf("found %c at %d\n", 101, 241);
                                        } else {
                                            hash ^= 58106962663219724;
                                        }
                                    } else if (flag[198] == 'w') {
                                        hash ^= 41454277597722044;
                                        printf("found %c at %d\n", 119, 198);
                                        if (flag[42] == '4') {
                                            hash ^= 59498810153749694;
                                            printf("found %c at %d\n", 52, 42);
                                        } else if (flag[118] == '}') {
                                            hash ^= 57155449393076784;
                                            printf("found %c at %d\n", 125, 118);
                                        } else {
                                            hash ^= 44185230654968503;
                                        }
                                    } else {
                                        hash ^= 47801965440397698;
                                    }
                                } else {
                                    hash ^= 42396381154645531;
                                }
                            } else if (flag[155] == '2') {
                                hash ^= 59450965426770235;
                                printf("found %c at %d\n", 50, 155);
                                if (flag[112] == 'Z') {
                                    hash ^= 49292556682967614;
                                    printf("found %c at %d\n", 90, 112);
                                    if (flag[229] == '7') {
                                        hash ^= 56443701843376864;
                                        printf("found %c at %d\n", 55, 229);
                                        if (flag[96] == 'd') {
                                            hash ^= 54840879584936177;
                                            printf("found %c at %d\n", 100, 96);
                                        } else if (flag[166] == 'n') {
                                            hash ^= 41836212658600456;
                                            printf("found %c at %d\n", 110, 166);
                                        } else {
                                            hash ^= 64089688617724802;
                                        }
                                    } else if (flag[110] == '7') {
                                        hash ^= 53589767472426704;
                                        printf("found %c at %d\n", 55, 110);
                                        if (flag[212] == 'd') {
                                            hash ^= 61274582825846453;
                                            printf("found %c at %d\n", 100, 212);
                                        } else if (flag[241] == 'Y') {
                                            hash ^= 63232453836056419;
                                            printf("found %c at %d\n", 89, 241);
                                        } else {
                                            hash ^= 65495807510215636;
                                        }
                                    } else {
                                        hash ^= 61645327077837871;
                                    }
                                } else if (flag[154] == 'W') {
                                    hash ^= 71821595872369969;
                                    printf("found %c at %d\n", 87, 154);
                                    if (flag[88] == 'r') {
                                        hash ^= 70065837444837229;
                                        printf("found %c at %d\n", 114, 88);
                                        if (flag[169] == 'l') {
                                            hash ^= 53618297854647207;
                                            printf("found %c at %d\n", 108, 169);
                                        } else if (flag[210] == 'Y') {
                                            hash ^= 68019828517748473;
                                            printf("found %c at %d\n", 89, 210);
                                        } else {
                                            hash ^= 65444631704617831;
                                        }
                                    } else if (flag[22] == 'E') {
                                        hash ^= 61750247226380540;
                                        printf("found %c at %d\n", 69, 22);
                                        if (flag[190] == 'X') {
                                            hash ^= 59416174800948258;
                                            printf("found %c at %d\n", 88, 190);
                                        } else if (flag[211] == 'v') {
                                            hash ^= 59540727640697479;
                                            printf("found %c at %d\n", 118, 211);
                                        } else {
                                            hash ^= 47002662592181397;
                                        }
                                    } else {
                                        hash ^= 56338141915514487;
                                    }
                                } else {
                                    hash ^= 40459372440021918;
                                }
                            } else {
                                hash ^= 38511980624483202;
                            }
                        } else if (flag[23] == 'O') {
                            hash ^= 62083198957115718;
                            printf("found %c at %d\n", 79, 23);
                            if (flag[68] == '1') {
                                hash ^= 58586291580373982;
                                printf("found %c at %d\n", 49, 68);
                                if (flag[197] == 'W') {
                                    hash ^= 54568789923537505;
                                    printf("found %c at %d\n", 87, 197);
                                    if (flag[236] == 'R') {
                                        hash ^= 54029703849561931;
                                        printf("found %c at %d\n", 82, 236);
                                        if (flag[216] == 'I') {
                                            hash ^= 44621158240730819;
                                            printf("found %c at %d\n", 73, 216);
                                        } else if (flag[178] == 'V') {
                                            hash ^= 61590462896675284;
                                            printf("found %c at %d\n", 86, 178);
                                        } else {
                                            hash ^= 37891777412711784;
                                        }
                                    } else if (flag[197] == 'p') {
                                        hash ^= 36150984380066856;
                                        printf("found %c at %d\n", 112, 197);
                                        if (flag[72] == 'b') {
                                            hash ^= 43733533668676647;
                                            printf("found %c at %d\n", 98, 72);
                                        } else if (flag[198] == 'M') {
                                            hash ^= 61205229199237518;
                                            printf("found %c at %d\n", 77, 198);
                                        } else {
                                            hash ^= 56360671064932225;
                                        }
                                    } else {
                                        hash ^= 71947200765172960;
                                    }
                                } else if (flag[221] == 'o') {
                                    hash ^= 44124326689267014;
                                    printf("found %c at %d\n", 111, 221);
                                    if (flag[124] == 'J') {
                                        hash ^= 40568261941045950;
                                        printf("found %c at %d\n", 74, 124);
                                        if (flag[115] == 'N') {
                                            hash ^= 60110674316032288;
                                            printf("found %c at %d\n", 78, 115);
                                        } else if (flag[60] == 'l') {
                                            hash ^= 65327463493668273;
                                            printf("found %c at %d\n", 108, 60);
                                        } else {
                                            hash ^= 40731170948972259;
                                        }
                                    } else if (flag[126] == 'V') {
                                        hash ^= 66688022227107865;
                                        printf("found %c at %d\n", 86, 126);
                                        if (flag[61] == 'P') {
                                            hash ^= 56479828718298309;
                                            printf("found %c at %d\n", 80, 61);
                                        } else if (flag[104] == 'O') {
                                            hash ^= 71502675067282706;
                                            printf("found %c at %d\n", 79, 104);
                                        } else {
                                            hash ^= 61682671478545132;
                                        }
                                    } else {
                                        hash ^= 62044561085043558;
                                    }
                                } else {
                                    hash ^= 58704953983318852;
                                }
                            } else if (flag[199] == '8') {
                                hash ^= 40788059277576677;
                                printf("found %c at %d\n", 56, 199);
                                if (flag[187] == 'H') {
                                    hash ^= 65364749480464391;
                                    printf("found %c at %d\n", 72, 187);
                                    if (flag[137] == 'T') {
                                        hash ^= 56798201382004738;
                                        printf("found %c at %d\n", 84, 137);
                                        if (flag[25] == 'Q') {
                                            hash ^= 56794710968889596;
                                            printf("found %c at %d\n", 81, 25);
                                        } else if (flag[97] == 'W') {
                                            hash ^= 59768465210915212;
                                            printf("found %c at %d\n", 87, 97);
                                        } else {
                                            hash ^= 58790767588973743;
                                        }
                                    } else if (flag[236] == '7') {
                                        hash ^= 54827620074016173;
                                        printf("found %c at %d\n", 55, 236);
                                        if (flag[36] == 'v') {
                                            hash ^= 46947187267227559;
                                            printf("found %c at %d\n", 118, 36);
                                        } else if (flag[159] == 'X') {
                                            hash ^= 39577671732513844;
                                            printf("found %c at %d\n", 88, 159);
                                        } else {
                                            hash ^= 69198468772941657;
                                        }
                                    } else {
                                        hash ^= 59343363387642464;
                                    }
                                } else if (flag[114] == 'l') {
                                    hash ^= 58183765983283379;
                                    printf("found %c at %d\n", 108, 114);
                                    if (flag[203] == 'C') {
                                        hash ^= 37123915452222699;
                                        printf("found %c at %d\n", 67, 203);
                                        if (flag[192] == 'L') {
                                            hash ^= 70489725393033445;
                                            printf("found %c at %d\n", 76, 192);
                                        } else if (flag[105] == 'm') {
                                            hash ^= 68609482882634067;
                                            printf("found %c at %d\n", 109, 105);
                                        } else {
                                            hash ^= 44164384546466161;
                                        }
                                    } else if (flag[138] == '2') {
                                        hash ^= 59542003258764867;
                                        printf("found %c at %d\n", 50, 138);
                                        if (flag[117] == 'e') {
                                            hash ^= 64985281374732509;
                                            printf("found %c at %d\n", 101, 117);
                                        } else if (flag[153] == 'E') {
                                            hash ^= 62827388538155465;
                                            printf("found %c at %d\n", 69, 153);
                                        } else {
                                            hash ^= 69617201622959207;
                                        }
                                    } else {
                                        hash ^= 43135010045118958;
                                    }
                                } else {
                                    hash ^= 36814231610176683;
                                }
                            } else {
                                hash ^= 62834426324831902;
                            }
                        } else {
                            hash ^= 51968137625337131;
                        }
                    } else {
                        hash ^= 66087945082093446;
                    }
                } else if (flag[173] == 'm') {
                    hash ^= 68565129561563824;
                    printf("found %c at %d\n", 109, 173);
                    if (flag[0] == 'X') {
                        hash ^= 40963269539866117;
                        printf("found %c at %d\n", 88, 0);
                        if (flag[208] == '}') {
                            hash ^= 41121796670156109;
                            printf("found %c at %d\n", 125, 208);
                            if (flag[15] == 'X') {
                                hash ^= 63206905345981134;
                                printf("found %c at %d\n", 88, 15);
                                if (flag[39] == 'd') {
                                    hash ^= 54454244201420534;
                                    printf("found %c at %d\n", 100, 39);
                                    if (flag[160] == 'U') {
                                        hash ^= 59150882511534850;
                                        printf("found %c at %d\n", 85, 160);
                                        if (flag[162] == 'n') {
                                            hash ^= 57384383198829345;
                                            printf("found %c at %d\n", 110, 162);
                                        } else if (flag[43] == '3') {
                                            hash ^= 67927632026135075;
                                            printf("found %c at %d\n", 51, 43);
                                        } else {
                                            hash ^= 39859198267004904;
                                        }
                                    } else if (flag[173] == '}') {
                                        hash ^= 61065997866017206;
                                        printf("found %c at %d\n", 125, 173);
                                        if (flag[12] == 'v') {
                                            hash ^= 38001797986328411;
                                            printf("found %c at %d\n", 118, 12);
                                        } else if (flag[98] == 'g') {
                                            hash ^= 59034620679331301;
                                            printf("found %c at %d\n", 103, 98);
                                        } else {
                                            hash ^= 40614417067535549;
                                        }
                                    } else {
                                        hash ^= 41234439656182070;
                                    }
                                } else if (flag[92] == 'I') {
                                    hash ^= 43516991112738611;
                                    printf("found %c at %d\n", 73, 92);
                                    if (flag[229] == 'P') {
                                        hash ^= 42471253223486391;
                                        printf("found %c at %d\n", 80, 229);
                                        if (flag[189] == 'r') {
                                            hash ^= 54447175806689897;
                                            printf("found %c at %d\n", 114, 189);
                                        } else if (flag[104] == 'P') {
                                            hash ^= 70419376072958328;
                                            printf("found %c at %d\n", 80, 104);
                                        } else {
                                            hash ^= 51549615240146274;
                                        }
                                    } else if (flag[20] == 'o') {
                                        hash ^= 48479012581793572;
                                        printf("found %c at %d\n", 111, 20);
                                        if (flag[81] == '2') {
                                            hash ^= 62790952687844450;
                                            printf("found %c at %d\n", 50, 81);
                                        } else if (flag[152] == 'b') {
                                            hash ^= 47652604619814067;
                                            printf("found %c at %d\n", 98, 152);
                                        } else {
                                            hash ^= 46684529950488012;
                                        }
                                    } else {
                                        hash ^= 60215693128149856;
                                    }
                                } else {
                                    hash ^= 66231234563109702;
                                }
                            } else if (flag[6] == 'V') {
                                hash ^= 69507566536117858;
                                printf("found %c at %d\n", 86, 6);
                                if (flag[110] == 'T') {
                                    hash ^= 65113833497303130;
                                    printf("found %c at %d\n", 84, 110);
                                    if (flag[78] == '6') {
                                        hash ^= 43478503104589151;
                                        printf("found %c at %d\n", 54, 78);
                                        if (flag[128] == 'Y') {
                                            hash ^= 39142246633224830;
                                            printf("found %c at %d\n", 89, 128);
                                        } else if (flag[147] == 'h') {
                                            hash ^= 45357267671879106;
                                            printf("found %c at %d\n", 104, 147);
                                        } else {
                                            hash ^= 54382612746219322;
                                        }
                                    } else if (flag[61] == 'T') {
                                        hash ^= 71496500519950798;
                                        printf("found %c at %d\n", 84, 61);
                                        if (flag[169] == 'n') {
                                            hash ^= 55372255968791934;
                                            printf("found %c at %d\n", 110, 169);
                                        } else if (flag[108] == 'q') {
                                            hash ^= 55393199370259099;
                                            printf("found %c at %d\n", 113, 108);
                                        } else {
                                            hash ^= 69444621435520144;
                                        }
                                    } else {
                                        hash ^= 71271699017962425;
                                    }
                                } else if (flag[114] == 'i') {
                                    hash ^= 67585503971883971;
                                    printf("found %c at %d\n", 105, 114);
                                    if (flag[60] == 'r') {
                                        hash ^= 56505147583938540;
                                        printf("found %c at %d\n", 114, 60);
                                        if (flag[198] == 'x') {
                                            hash ^= 37129489759579488;
                                            printf("found %c at %d\n", 120, 198);
                                        } else if (flag[204] == 'D') {
                                            hash ^= 46037281635082819;
                                            printf("found %c at %d\n", 68, 204);
                                        } else {
                                            hash ^= 53828577349455865;
                                        }
                                    } else if (flag[91] == '{') {
                                        hash ^= 69662830062169193;
                                        printf("found %c at %d\n", 123, 91);
                                        if (flag[132] == 'q') {
                                            hash ^= 54750722418951561;
                                            printf("found %c at %d\n", 113, 132);
                                        } else if (flag[190] == 'e') {
                                            hash ^= 67639012276379805;
                                            printf("found %c at %d\n", 101, 190);
                                        } else {
                                            hash ^= 42403052060318976;
                                        }
                                    } else {
                                        hash ^= 59170395329219211;
                                    }
                                } else {
                                    hash ^= 60548785314679205;
                                }
                            } else {
                                hash ^= 42842120741919364;
                            }
                        } else if (flag[112] == 'M') {
                            hash ^= 55315652475996468;
                            printf("found %c at %d\n", 77, 112);
                            if (flag[153] == '1') {
                                hash ^= 65623166575043450;
                                printf("found %c at %d\n", 49, 153);
                                if (flag[197] == 'G') {
                                    hash ^= 61075539339204568;
                                    printf("found %c at %d\n", 71, 197);
                                    if (flag[195] == '4') {
                                        hash ^= 51875008650839661;
                                        printf("found %c at %d\n", 52, 195);
                                        if (flag[28] == 'N') {
                                            hash ^= 69053388854685202;
                                            printf("found %c at %d\n", 78, 28);
                                        } else if (flag[209] == 'I') {
                                            hash ^= 46669991409908630;
                                            printf("found %c at %d\n", 73, 209);
                                        } else {
                                            hash ^= 54692439174327285;
                                        }
                                    } else if (flag[118] == 'z') {
                                        hash ^= 43476793469934231;
                                        printf("found %c at %d\n", 122, 118);
                                        if (flag[55] == 'I') {
                                            hash ^= 60232469249890079;
                                            printf("found %c at %d\n", 73, 55);
                                        } else if (flag[223] == '5') {
                                            hash ^= 37934031760862195;
                                            printf("found %c at %d\n", 53, 223);
                                        } else {
                                            hash ^= 54303607767212964;
                                        }
                                    } else {
                                        hash ^= 37114556363496510;
                                    }
                                } else if (flag[149] == 'l') {
                                    hash ^= 65893242928738865;
                                    printf("found %c at %d\n", 108, 149);
                                    if (flag[250] == '}') {
                                        hash ^= 50915894611206306;
                                        printf("found %c at %d\n", 125, 250);
                                        if (flag[22] == 'L') {
                                            hash ^= 60238261194248182;
                                            printf("found %c at %d\n", 76, 22);
                                        } else if (flag[25] == 'x') {
                                            hash ^= 67656657570922511;
                                            printf("found %c at %d\n", 120, 25);
                                        } else {
                                            hash ^= 42786603121419539;
                                        }
                                    } else if (flag[158] == 'w') {
                                        hash ^= 37502937360036112;
                                        printf("found %c at %d\n", 119, 158);
                                        if (flag[172] == '4') {
                                            hash ^= 43731095528476809;
                                            printf("found %c at %d\n", 52, 172);
                                        } else if (flag[68] == 'p') {
                                            hash ^= 49600698792747389;
                                            printf("found %c at %d\n", 112, 68);
                                        } else {
                                            hash ^= 67980130846313863;
                                        }
                                    } else {
                                        hash ^= 67657042567483147;
                                    }
                                } else {
                                    hash ^= 64950789552748607;
                                }
                            } else if (flag[104] == 'q') {
                                hash ^= 47878116527843858;
                                printf("found %c at %d\n", 113, 104);
                                if (flag[80] == 'W') {
                                    hash ^= 71795289377940690;
                                    printf("found %c at %d\n", 87, 80);
                                    if (flag[171] == 'u') {
                                        hash ^= 69593762606755931;
                                        printf("found %c at %d\n", 117, 171);
                                        if (flag[77] == 'P') {
                                            hash ^= 45800793195881491;
                                            printf("found %c at %d\n", 80, 77);
                                        } else if (flag[78] == 't') {
                                            hash ^= 64604978751343377;
                                            printf("found %c at %d\n", 116, 78);
                                        } else {
                                            hash ^= 40397123558254942;
                                        }
                                    } else if (flag[123] == '_') {
                                        hash ^= 57473527668977728;
                                        printf("found %c at %d\n", 95, 123);
                                        if (flag[181] == 'g') {
                                            hash ^= 41288803480562435;
                                            printf("found %c at %d\n", 103, 181);
                                        } else if (flag[28] == '0') {
                                            hash ^= 52804077974255301;
                                            printf("found %c at %d\n", 48, 28);
                                        } else {
                                            hash ^= 46250306667872904;
                                        }
                                    } else {
                                        hash ^= 52649070208419475;
                                    }
                                } else if (flag[67] == 'y') {
                                    hash ^= 48602060007789709;
                                    printf("found %c at %d\n", 121, 67);
                                    if (flag[10] == 'c') {
                                        hash ^= 48195821610963616;
                                        printf("found %c at %d\n", 99, 10);
                                        if (flag[52] == 'd') {
                                            hash ^= 69629939386672460;
                                            printf("found %c at %d\n", 100, 52);
                                        } else if (flag[107] == 'n') {
                                            hash ^= 42766035048424706;
                                            printf("found %c at %d\n", 110, 107);
                                        } else {
                                            hash ^= 41358796247159612;
                                        }
                                    } else if (flag[218] == 'i') {
                                        hash ^= 43679337612913206;
                                        printf("found %c at %d\n", 105, 218);
                                        if (flag[44] == '}') {
                                            hash ^= 54495562836524353;
                                            printf("found %c at %d\n", 125, 44);
                                        } else if (flag[14] == 'Z') {
                                            hash ^= 40589701232448294;
                                            printf("found %c at %d\n", 90, 14);
                                        } else {
                                            hash ^= 44234206910809895;
                                        }
                                    } else {
                                        hash ^= 62967977123742121;
                                    }
                                } else {
                                    hash ^= 39708309714467151;
                                }
                            } else {
                                hash ^= 68675143570613614;
                            }
                        } else {
                            hash ^= 42438533346869876;
                        }
                    } else if (flag[254] == 'i') {
                        hash ^= 40330770151446258;
                        printf("found %c at %d\n", 105, 254);
                        if (flag[213] == '3') {
                            hash ^= 58702044285581034;
                            printf("found %c at %d\n", 51, 213);
                            if (flag[235] == '8') {
                                hash ^= 36119454251930307;
                                printf("found %c at %d\n", 56, 235);
                                if (flag[245] == 'T') {
                                    hash ^= 37415035393544851;
                                    printf("found %c at %d\n", 84, 245);
                                    if (flag[125] == 'Y') {
                                        hash ^= 58645798605644214;
                                        printf("found %c at %d\n", 89, 125);
                                        if (flag[168] == 'B') {
                                            hash ^= 60077707769350957;
                                            printf("found %c at %d\n", 66, 168);
                                        } else if (flag[237] == '3') {
                                            hash ^= 54790939629659292;
                                            printf("found %c at %d\n", 51, 237);
                                        } else {
                                            hash ^= 58883533158587691;
                                        }
                                    } else if (flag[94] == 'w') {
                                        hash ^= 42472893461057434;
                                        printf("found %c at %d\n", 119, 94);
                                        if (flag[203] == '5') {
                                            hash ^= 53959284141864760;
                                            printf("found %c at %d\n", 53, 203);
                                        } else if (flag[157] == 'A') {
                                            hash ^= 43100295520359309;
                                            printf("found %c at %d\n", 65, 157);
                                        } else {
                                            hash ^= 67226555581868602;
                                        }
                                    } else {
                                        hash ^= 56230797492919595;
                                    }
                                } else if (flag[115] == '{') {
                                    hash ^= 40374035285250691;
                                    printf("found %c at %d\n", 123, 115);
                                    if (flag[234] == '2') {
                                        hash ^= 48972037426270097;
                                        printf("found %c at %d\n", 50, 234);
                                        if (flag[190] == 'Z') {
                                            hash ^= 54057866826716909;
                                            printf("found %c at %d\n", 90, 190);
                                        } else if (flag[177] == '4') {
                                            hash ^= 51475580416898480;
                                            printf("found %c at %d\n", 52, 177);
                                        } else {
                                            hash ^= 42378655569174203;
                                        }
                                    } else if (flag[88] == 'O') {
                                        hash ^= 46863364020778109;
                                        printf("found %c at %d\n", 79, 88);
                                        if (flag[98] == 'w') {
                                            hash ^= 53337071186563736;
                                            printf("found %c at %d\n", 119, 98);
                                        } else if (flag[35] == '6') {
                                            hash ^= 55001791028112597;
                                            printf("found %c at %d\n", 54, 35);
                                        } else {
                                            hash ^= 46682271564665975;
                                        }
                                    } else {
                                        hash ^= 52469800921854065;
                                    }
                                } else {
                                    hash ^= 48882049780675229;
                                }
                            } else if (flag[122] == 'O') {
                                hash ^= 65738191634003213;
                                printf("found %c at %d\n", 79, 122);
                                if (flag[248] == 'q') {
                                    hash ^= 67632753765495014;
                                    printf("found %c at %d\n", 113, 248);
                                    if (flag[152] == 'e') {
                                        hash ^= 68302139991030453;
                                        printf("found %c at %d\n", 101, 152);
                                        if (flag[40] == 'U') {
                                            hash ^= 48543219546871282;
                                            printf("found %c at %d\n", 85, 40);
                                        } else if (flag[108] == '2') {
                                            hash ^= 61258649119028380;
                                            printf("found %c at %d\n", 50, 108);
                                        } else {
                                            hash ^= 66885308747089939;
                                        }
                                    } else if (flag[41] == 'c') {
                                        hash ^= 58557223201432593;
                                        printf("found %c at %d\n", 99, 41);
                                        if (flag[161] == 'A') {
                                            hash ^= 48143463644904669;
                                            printf("found %c at %d\n", 65, 161);
                                        } else if (flag[227] == 'Q') {
                                            hash ^= 54663922713649729;
                                            printf("found %c at %d\n", 81, 227);
                                        } else {
                                            hash ^= 52505284255638731;
                                        }
                                    } else {
                                        hash ^= 67242195667993210;
                                    }
                                } else if (flag[201] == 'l') {
                                    hash ^= 67914069332215964;
                                    printf("found %c at %d\n", 108, 201);
                                    if (flag[22] == 'P') {
                                        hash ^= 45758187281539804;
                                        printf("found %c at %d\n", 80, 22);
                                        if (flag[201] == 'G') {
                                            hash ^= 65912681937350197;
                                            printf("found %c at %d\n", 71, 201);
                                        } else if (flag[4] == 'D') {
                                            hash ^= 38725464236926948;
                                            printf("found %c at %d\n", 68, 4);
                                        } else {
                                            hash ^= 51177663693282668;
                                        }
                                    } else if (flag[141] == 'j') {
                                        hash ^= 41909540897394538;
                                        printf("found %c at %d\n", 106, 141);
                                        if (flag[160] == 'a') {
                                            hash ^= 44877222907566129;
                                            printf("found %c at %d\n", 97, 160);
                                        } else if (flag[166] == 'D') {
                                            hash ^= 42367197286343000;
                                            printf("found %c at %d\n", 68, 166);
                                        } else {
                                            hash ^= 54661369946645966;
                                        }
                                    } else {
                                        hash ^= 69888351809752695;
                                    }
                                } else {
                                    hash ^= 45468967310162353;
                                }
                            } else {
                                hash ^= 71734271694229746;
                            }
                        } else if (flag[233] == 'N') {
                            hash ^= 47577459478270849;
                            printf("found %c at %d\n", 78, 233);
                            if (flag[94] == '}') {
                                hash ^= 64577865406810527;
                                printf("found %c at %d\n", 125, 94);
                                if (flag[128] == 'I') {
                                    hash ^= 63427317910992824;
                                    printf("found %c at %d\n", 73, 128);
                                    if (flag[178] == 'b') {
                                        hash ^= 70276452330503915;
                                        printf("found %c at %d\n", 98, 178);
                                        if (flag[128] == '7') {
                                            hash ^= 37891079181797668;
                                            printf("found %c at %d\n", 55, 128);
                                        } else if (flag[124] == 'p') {
                                            hash ^= 58265170793425093;
                                            printf("found %c at %d\n", 112, 124);
                                        } else {
                                            hash ^= 55073364797842135;
                                        }
                                    } else if (flag[26] == 'y') {
                                        hash ^= 57984014788936909;
                                        printf("found %c at %d\n", 121, 26);
                                        if (flag[30] == '3') {
                                            hash ^= 71744372046789719;
                                            printf("found %c at %d\n", 51, 30);
                                        } else if (flag[190] == 'C') {
                                            hash ^= 68023315491764310;
                                            printf("found %c at %d\n", 67, 190);
                                        } else {
                                            hash ^= 67726338844087465;
                                        }
                                    } else {
                                        hash ^= 42962146921488317;
                                    }
                                } else if (flag[243] == 'q') {
                                    hash ^= 61068513358566238;
                                    printf("found %c at %d\n", 113, 243);
                                    if (flag[161] == '2') {
                                        hash ^= 71396425564896916;
                                        printf("found %c at %d\n", 50, 161);
                                        if (flag[31] == 'U') {
                                            hash ^= 38472802054199888;
                                            printf("found %c at %d\n", 85, 31);
                                        } else if (flag[12] == 'b') {
                                            hash ^= 49590121374135962;
                                            printf("found %c at %d\n", 98, 12);
                                        } else {
                                            hash ^= 48433624607056181;
                                        }
                                    } else if (flag[161] == 'u') {
                                        hash ^= 68149439833541064;
                                        printf("found %c at %d\n", 117, 161);
                                        if (flag[249] == 'v') {
                                            hash ^= 70556712509044578;
                                            printf("found %c at %d\n", 118, 249);
                                        } else if (flag[244] == 'y') {
                                            hash ^= 63189474071606762;
                                            printf("found %c at %d\n", 121, 244);
                                        } else {
                                            hash ^= 67015719808131135;
                                        }
                                    } else {
                                        hash ^= 54714099329547198;
                                    }
                                } else {
                                    hash ^= 41111546764566483;
                                }
                            } else if (flag[148] == 'u') {
                                hash ^= 66321679043372729;
                                printf("found %c at %d\n", 117, 148);
                                if (flag[199] == 'u') {
                                    hash ^= 56074335952147392;
                                    printf("found %c at %d\n", 117, 199);
                                    if (flag[225] == 'v') {
                                        hash ^= 47785757331567098;
                                        printf("found %c at %d\n", 118, 225);
                                        if (flag[19] == 'e') {
                                            hash ^= 50392035639505438;
                                            printf("found %c at %d\n", 101, 19);
                                        } else if (flag[78] == 'D') {
                                            hash ^= 46675396216536887;
                                            printf("found %c at %d\n", 68, 78);
                                        } else {
                                            hash ^= 59192345240514454;
                                        }
                                    } else if (flag[15] == 'P') {
                                        hash ^= 44471772517709330;
                                        printf("found %c at %d\n", 80, 15);
                                        if (flag[97] == 'r') {
                                            hash ^= 44475793672088092;
                                            printf("found %c at %d\n", 114, 97);
                                        } else if (flag[139] == 'c') {
                                            hash ^= 39348492325648413;
                                            printf("found %c at %d\n", 99, 139);
                                        } else {
                                            hash ^= 70009850849054107;
                                        }
                                    } else {
                                        hash ^= 65428181174158673;
                                    }
                                } else if (flag[175] == 'r') {
                                    hash ^= 49040494070812739;
                                    printf("found %c at %d\n", 114, 175);
                                    if (flag[191] == 'd') {
                                        hash ^= 49559345824130927;
                                        printf("found %c at %d\n", 100, 191);
                                        if (flag[235] == 'v') {
                                            hash ^= 48413151272252793;
                                            printf("found %c at %d\n", 118, 235);
                                        } else if (flag[249] == 'K') {
                                            hash ^= 67813040444299155;
                                            printf("found %c at %d\n", 75, 249);
                                        } else {
                                            hash ^= 52435676265291722;
                                        }
                                    } else if (flag[177] == '9') {
                                        hash ^= 67797388576290692;
                                        printf("found %c at %d\n", 57, 177);
                                        if (flag[140] == 'l') {
                                            hash ^= 39537453565646922;
                                            printf("found %c at %d\n", 108, 140);
                                        } else if (flag[176] == 'd') {
                                            hash ^= 62403823670300576;
                                            printf("found %c at %d\n", 100, 176);
                                        } else {
                                            hash ^= 37913719754754060;
                                        }
                                    } else {
                                        hash ^= 55041263489738446;
                                    }
                                } else {
                                    hash ^= 63399635411023890;
                                }
                            } else {
                                hash ^= 56975178688445643;
                            }
                        } else {
                            hash ^= 53595194058077534;
                        }
                    } else {
                        hash ^= 45706043676056241;
                    }
                } else {
                    hash ^= 57542625643992676;
                }
            } else {
                hash ^= 42761663646318280;
            }
        } else if (flag[232] == 'i') {
            hash ^= 47115977641306083;
            printf("found %c at %d\n", 105, 232);
            if (flag[170] == 'Y') {
                hash ^= 66570062088191134;
                printf("found %c at %d\n", 89, 170);
                if (flag[72] == 'A') {
                    hash ^= 58794292330892491;
                    printf("found %c at %d\n", 65, 72);
                    if (flag[54] == 'N') {
                        hash ^= 65569736102187167;
                        printf("found %c at %d\n", 78, 54);
                        if (flag[221] == 'K') {
                            hash ^= 44346289560395040;
                            printf("found %c at %d\n", 75, 221);
                            if (flag[155] == 'C') {
                                hash ^= 60099261588483052;
                                printf("found %c at %d\n", 67, 155);
                                if (flag[84] == 'g') {
                                    hash ^= 44336210954181195;
                                    printf("found %c at %d\n", 103, 84);
                                    if (flag[124] == 'c') {
                                        hash ^= 37836587028086707;
                                        printf("found %c at %d\n", 99, 124);
                                        if (flag[33] == 'g') {
                                            hash ^= 71945867749167181;
                                            printf("found %c at %d\n", 103, 33);
                                        } else if (flag[182] == 'b') {
                                            hash ^= 66426570666676094;
                                            printf("found %c at %d\n", 98, 182);
                                        } else {
                                            hash ^= 64930142627309807;
                                        }
                                    } else if (flag[162] == '4') {
                                        hash ^= 55269280189316311;
                                        printf("found %c at %d\n", 52, 162);
                                        if (flag[108] == 'G') {
                                            hash ^= 54897647958935372;
                                            printf("found %c at %d\n", 71, 108);
                                        } else if (flag[213] == 'W') {
                                            hash ^= 37068037244572819;
                                            printf("found %c at %d\n", 87, 213);
                                        } else {
                                            hash ^= 49511256923103819;
                                        }
                                    } else {
                                        hash ^= 64377488091339746;
                                    }
                                } else if (flag[110] == 'V') {
                                    hash ^= 39752017603598244;
                                    printf("found %c at %d\n", 86, 110);
                                    if (flag[166] == 'P') {
                                        hash ^= 65869706448478273;
                                        printf("found %c at %d\n", 80, 166);
                                        if (flag[136] == 'x') {
                                            hash ^= 60554793285701830;
                                            printf("found %c at %d\n", 120, 136);
                                        } else if (flag[247] == 'v') {
                                            hash ^= 54030613064275550;
                                            printf("found %c at %d\n", 118, 247);
                                        } else {
                                            hash ^= 47355559552717270;
                                        }
                                    } else if (flag[231] == 'M') {
                                        hash ^= 37440435413305058;
                                        printf("found %c at %d\n", 77, 231);
                                        if (flag[237] == 'M') {
                                            hash ^= 41159925368415891;
                                            printf("found %c at %d\n", 77, 237);
                                        } else if (flag[175] == 'V') {
                                            hash ^= 43821935506522506;
                                            printf("found %c at %d\n", 86, 175);
                                        } else {
                                            hash ^= 62669389655129113;
                                        }
                                    } else {
                                        hash ^= 53323383095308521;
                                    }
                                } else {
                                    hash ^= 65450249973433903;
                                }
                            } else if (flag[68] == 'Z') {
                                hash ^= 68761351115500310;
                                printf("found %c at %d\n", 90, 68);
                                if (flag[82] == 'k') {
                                    hash ^= 56095456869648598;
                                    printf("found %c at %d\n", 107, 82);
                                    if (flag[111] == '5') {
                                        hash ^= 49113087354491264;
                                        printf("found %c at %d\n", 53, 111);
                                        if (flag[145] == 'V') {
                                            hash ^= 58959917256896028;
                                            printf("found %c at %d\n", 86, 145);
                                        } else if (flag[20] == 'z') {
                                            hash ^= 58281103841705527;
                                            printf("found %c at %d\n", 122, 20);
                                        } else {
                                            hash ^= 70316253547440224;
                                        }
                                    } else if (flag[3] == 'z') {
                                        hash ^= 37511592093391928;
                                        printf("found %c at %d\n", 122, 3);
                                        if (flag[55] == '7') {
                                            hash ^= 70677042184704624;
                                            printf("found %c at %d\n", 55, 55);
                                        } else if (flag[132] == 'a') {
                                            hash ^= 68993613028401661;
                                            printf("found %c at %d\n", 97, 132);
                                        } else {
                                            hash ^= 41449935076112924;
                                        }
                                    } else {
                                        hash ^= 67571694772976554;
                                    }
                                } else if (flag[160] == 'L') {
                                    hash ^= 63672944513925161;
                                    printf("found %c at %d\n", 76, 160);
                                    if (flag[99] == 'S') {
                                        hash ^= 51836284040246773;
                                        printf("found %c at %d\n", 83, 99);
                                        if (flag[9] == 'P') {
                                            hash ^= 62915253287437901;
                                            printf("found %c at %d\n", 80, 9);
                                        } else if (flag[156] == '6') {
                                            hash ^= 59908734856243924;
                                            printf("found %c at %d\n", 54, 156);
                                        } else {
                                            hash ^= 48259785642735993;
                                        }
                                    } else if (flag[245] == 's') {
                                        hash ^= 43221032470911433;
                                        printf("found %c at %d\n", 115, 245);
                                        if (flag[81] == 'I') {
                                            hash ^= 56897669877719712;
                                            printf("found %c at %d\n", 73, 81);
                                        } else if (flag[177] == 'D') {
                                            hash ^= 64030924954637425;
                                            printf("found %c at %d\n", 68, 177);
                                        } else {
                                            hash ^= 47182714023053811;
                                        }
                                    } else {
                                        hash ^= 66359044612536867;
                                    }
                                } else {
                                    hash ^= 60314892348179244;
                                }
                            } else {
                                hash ^= 71698029480871624;
                            }
                        } else if (flag[66] == 'O') {
                            hash ^= 48962817286425775;
                            printf("found %c at %d\n", 79, 66);
                            if (flag[109] == '1') {
                                hash ^= 55925167858545618;
                                printf("found %c at %d\n", 49, 109);
                                if (flag[231] == 'u') {
                                    hash ^= 54143723599958733;
                                    printf("found %c at %d\n", 117, 231);
                                    if (flag[68] == 'I') {
                                        hash ^= 69291904363412299;
                                        printf("found %c at %d\n", 73, 68);
                                        if (flag[165] == 'x') {
                                            hash ^= 45520228107997581;
                                            printf("found %c at %d\n", 120, 165);
                                        } else if (flag[195] == 'N') {
                                            hash ^= 60966205631857280;
                                            printf("found %c at %d\n", 78, 195);
                                        } else {
                                            hash ^= 46008705510628590;
                                        }
                                    } else if (flag[1] == 'h') {
                                        hash ^= 42547261925759002;
                                        printf("found %c at %d\n", 104, 1);
                                        if (flag[118] == 'R') {
                                            hash ^= 44047099861435020;
                                            printf("found %c at %d\n", 82, 118);
                                        } else if (flag[254] == 'y') {
                                            hash ^= 56716850416514516;
                                            printf("found %c at %d\n", 121, 254);
                                        } else {
                                            hash ^= 42833384676228803;
                                        }
                                    } else {
                                        hash ^= 56571083714725690;
                                    }
                                } else if (flag[14] == 'K') {
                                    hash ^= 45420782964029695;
                                    printf("found %c at %d\n", 75, 14);
                                    if (flag[162] == 'Q') {
                                        hash ^= 59763009192137150;
                                        printf("found %c at %d\n", 81, 162);
                                        if (flag[15] == 'j') {
                                            hash ^= 39369695998020838;
                                            printf("found %c at %d\n", 106, 15);
                                        } else if (flag[224] == 'k') {
                                            hash ^= 57305957344967807;
                                            printf("found %c at %d\n", 107, 224);
                                        } else {
                                            hash ^= 47159582554905815;
                                        }
                                    } else if (flag[16] == 'b') {
                                        hash ^= 71690737007143109;
                                        printf("found %c at %d\n", 98, 16);
                                        if (flag[35] == 'T') {
                                            hash ^= 44716264512305151;
                                            printf("found %c at %d\n", 84, 35);
                                        } else if (flag[128] == 'v') {
                                            hash ^= 47161367736485671;
                                            printf("found %c at %d\n", 118, 128);
                                        } else {
                                            hash ^= 41388996873288430;
                                        }
                                    } else {
                                        hash ^= 58023446827290917;
                                    }
                                } else {
                                    hash ^= 37432316342081543;
                                }
                            } else if (flag[223] == 'C') {
                                hash ^= 71826683964022789;
                                printf("found %c at %d\n", 67, 223);
                                if (flag[218] == 'd') {
                                    hash ^= 49736111916371868;
                                    printf("found %c at %d\n", 100, 218);
                                    if (flag[255] == 'b') {
                                        hash ^= 38164536854946733;
                                        printf("found %c at %d\n", 98, 255);
                                        if (flag[37] == 'c') {
                                            hash ^= 39591054241540019;
                                            printf("found %c at %d\n", 99, 37);
                                        } else if (flag[156] == 'H') {
                                            hash ^= 40990630114624073;
                                            printf("found %c at %d\n", 72, 156);
                                        } else {
                                            hash ^= 65545665135924653;
                                        }
                                    } else if (flag[215] == 'h') {
                                        hash ^= 66972152851519960;
                                        printf("found %c at %d\n", 104, 215);
                                        if (flag[247] == 'd') {
                                            hash ^= 50877951061670719;
                                            printf("found %c at %d\n", 100, 247);
                                        } else if (flag[112] == 'j') {
                                            hash ^= 67808099683591117;
                                            printf("found %c at %d\n", 106, 112);
                                        } else {
                                            hash ^= 52728789818930513;
                                        }
                                    } else {
                                        hash ^= 47733614203421968;
                                    }
                                } else if (flag[14] == 'B') {
                                    hash ^= 58180150604802394;
                                    printf("found %c at %d\n", 66, 14);
                                    if (flag[52] == 'p') {
                                        hash ^= 56110595233691730;
                                        printf("found %c at %d\n", 112, 52);
                                        if (flag[4] == '3') {
                                            hash ^= 69769473051329578;
                                            printf("found %c at %d\n", 51, 4);
                                        } else if (flag[120] == 'R') {
                                            hash ^= 62311476533197057;
                                            printf("found %c at %d\n", 82, 120);
                                        } else {
                                            hash ^= 61430424442773884;
                                        }
                                    } else if (flag[13] == 'D') {
                                        hash ^= 36096942168704633;
                                        printf("found %c at %d\n", 68, 13);
                                        if (flag[24] == 'R') {
                                            hash ^= 59840373892151712;
                                            printf("found %c at %d\n", 82, 24);
                                        } else if (flag[195] == 'M') {
                                            hash ^= 51597771595293231;
                                            printf("found %c at %d\n", 77, 195);
                                        } else {
                                            hash ^= 40224459999016502;
                                        }
                                    } else {
                                        hash ^= 52775073747298829;
                                    }
                                } else {
                                    hash ^= 59397238771710874;
                                }
                            } else {
                                hash ^= 43657858048889109;
                            }
                        } else {
                            hash ^= 44181174610814270;
                        }
                    } else if (flag[225] == 'T') {
                        hash ^= 38937083049494804;
                        printf("found %c at %d\n", 84, 225);
                        if (flag[159] == 'v') {
                            hash ^= 54306883412167944;
                            printf("found %c at %d\n", 118, 159);
                            if (flag[149] == '2') {
                                hash ^= 57696442373504555;
                                printf("found %c at %d\n", 50, 149);
                                if (flag[224] == 'Y') {
                                    hash ^= 59878257391039652;
                                    printf("found %c at %d\n", 89, 224);
                                    if (flag[52] == 'V') {
                                        hash ^= 58355683174699452;
                                        printf("found %c at %d\n", 86, 52);
                                        if (flag[110] == 'O') {
                                            hash ^= 56515422991220621;
                                            printf("found %c at %d\n", 79, 110);
                                        } else if (flag[31] == 'r') {
                                            hash ^= 53170894046090149;
                                            printf("found %c at %d\n", 114, 31);
                                        } else {
                                            hash ^= 45860861635931630;
                                        }
                                    } else if (flag[154] == 'r') {
                                        hash ^= 71822325250662531;
                                        printf("found %c at %d\n", 114, 154);
                                        if (flag[234] == 'l') {
                                            hash ^= 43186321418082024;
                                            printf("found %c at %d\n", 108, 234);
                                        } else if (flag[41] == 'C') {
                                            hash ^= 42146707159390951;
                                            printf("found %c at %d\n", 67, 41);
                                        } else {
                                            hash ^= 60927075470368893;
                                        }
                                    } else {
                                        hash ^= 68954098799379205;
                                    }
                                } else if (flag[63] == '1') {
                                    hash ^= 61166144396407782;
                                    printf("found %c at %d\n", 49, 63);
                                    if (flag[247] == 'y') {
                                        hash ^= 46892542310886014;
                                        printf("found %c at %d\n", 121, 247);
                                        if (flag[149] == 'd') {
                                            hash ^= 52044882686032208;
                                            printf("found %c at %d\n", 100, 149);
                                        } else if (flag[161] == 'k') {
                                            hash ^= 66864004577419699;
                                            printf("found %c at %d\n", 107, 161);
                                        } else {
                                            hash ^= 50973454433551264;
                                        }
                                    } else if (flag[28] == '7') {
                                        hash ^= 56553090542002457;
                                        printf("found %c at %d\n", 55, 28);
                                        if (flag[143] == 'r') {
                                            hash ^= 49648168740123052;
                                            printf("found %c at %d\n", 114, 143);
                                        } else if (flag[17] == 'U') {
                                            hash ^= 57484977266935196;
                                            printf("found %c at %d\n", 85, 17);
                                        } else {
                                            hash ^= 57434939936913854;
                                        }
                                    } else {
                                        hash ^= 51723414043086775;
                                    }
                                } else {
                                    hash ^= 50724277633820637;
                                }
                            } else if (flag[208] == '3') {
                                hash ^= 71865592703637871;
                                printf("found %c at %d\n", 51, 208);
                                if (flag[75] == 'U') {
                                    hash ^= 68622434187513352;
                                    printf("found %c at %d\n", 85, 75);
                                    if (flag[99] == '7') {
                                        hash ^= 45961330002464556;
                                        printf("found %c at %d\n", 55, 99);
                                        if (flag[32] == 'B') {
                                            hash ^= 64632506724547578;
                                            printf("found %c at %d\n", 66, 32);
                                        } else if (flag[60] == '4') {
                                            hash ^= 48813391271619022;
                                            printf("found %c at %d\n", 52, 60);
                                        } else {
                                            hash ^= 58694571768053597;
                                        }
                                    } else if (flag[91] == 'P') {
                                        hash ^= 42835351016974842;
                                        printf("found %c at %d\n", 80, 91);
                                        if (flag[230] == 'Q') {
                                            hash ^= 68512358071043756;
                                            printf("found %c at %d\n", 81, 230);
                                        } else if (flag[178] == 'T') {
                                            hash ^= 40946328853290279;
                                            printf("found %c at %d\n", 84, 178);
                                        } else {
                                            hash ^= 42995072869381801;
                                        }
                                    } else {
                                        hash ^= 47235742585366094;
                                    }
                                } else if (flag[105] == '_') {
                                    hash ^= 67586501780546916;
                                    printf("found %c at %d\n", 95, 105);
                                    if (flag[84] == 'C') {
                                        hash ^= 68357232854259722;
                                        printf("found %c at %d\n", 67, 84);
                                        if (flag[179] == '2') {
                                            hash ^= 62153574669089175;
                                            printf("found %c at %d\n", 50, 179);
                                        } else if (flag[160] == 'O') {
                                            hash ^= 64134204025033963;
                                            printf("found %c at %d\n", 79, 160);
                                        } else {
                                            hash ^= 44072405107953988;
                                        }
                                    } else if (flag[89] == 'y') {
                                        hash ^= 70189343197791534;
                                        printf("found %c at %d\n", 121, 89);
                                        if (flag[91] == 'k') {
                                            hash ^= 44254083619610911;
                                            printf("found %c at %d\n", 107, 91);
                                        } else if (flag[84] == 'k') {
                                            hash ^= 42071108673490623;
                                            printf("found %c at %d\n", 107, 84);
                                        } else {
                                            hash ^= 48598793384364017;
                                        }
                                    } else {
                                        hash ^= 63470089592119318;
                                    }
                                } else {
                                    hash ^= 55558091343739478;
                                }
                            } else {
                                hash ^= 55173620703452740;
                            }
                        } else if (flag[115] == 'Z') {
                            hash ^= 67383755813146050;
                            printf("found %c at %d\n", 90, 115);
                            if (flag[161] == 'c') {
                                hash ^= 67558059451551889;
                                printf("found %c at %d\n", 99, 161);
                                if (flag[114] == 'Y') {
                                    hash ^= 38834413273793345;
                                    printf("found %c at %d\n", 89, 114);
                                    if (flag[30] == 'n') {
                                        hash ^= 45424603808012987;
                                        printf("found %c at %d\n", 110, 30);
                                        if (flag[65] == 'o') {
                                            hash ^= 42187409707969263;
                                            printf("found %c at %d\n", 111, 65);
                                        } else if (flag[67] == 'W') {
                                            hash ^= 55065664248530012;
                                            printf("found %c at %d\n", 87, 67);
                                        } else {
                                            hash ^= 40515825075163184;
                                        }
                                    } else if (flag[119] == 'X') {
                                        hash ^= 48084399382426590;
                                        printf("found %c at %d\n", 88, 119);
                                        if (flag[243] == 'L') {
                                            hash ^= 36748457023648642;
                                            printf("found %c at %d\n", 76, 243);
                                        } else if (flag[141] == 'n') {
                                            hash ^= 59452676299118036;
                                            printf("found %c at %d\n", 110, 141);
                                        } else {
                                            hash ^= 71770390801251290;
                                        }
                                    } else {
                                        hash ^= 52828895712338025;
                                    }
                                } else if (flag[240] == 'a') {
                                    hash ^= 54779470958850589;
                                    printf("found %c at %d\n", 97, 240);
                                    if (flag[173] == 'I') {
                                        hash ^= 66675234120714316;
                                        printf("found %c at %d\n", 73, 173);
                                        if (flag[136] == 'U') {
                                            hash ^= 53227608526189670;
                                            printf("found %c at %d\n", 85, 136);
                                        } else if (flag[116] == 'q') {
                                            hash ^= 47080337246622797;
                                            printf("found %c at %d\n", 113, 116);
                                        } else {
                                            hash ^= 43990696487302489;
                                        }
                                    } else if (flag[36] == 'm') {
                                        hash ^= 63084385282623423;
                                        printf("found %c at %d\n", 109, 36);
                                        if (flag[41] == 'b') {
                                            hash ^= 50807524328797899;
                                            printf("found %c at %d\n", 98, 41);
                                        } else if (flag[23] == '6') {
                                            hash ^= 61834987243466927;
                                            printf("found %c at %d\n", 54, 23);
                                        } else {
                                            hash ^= 63780644974486795;
                                        }
                                    } else {
                                        hash ^= 63601772132873013;
                                    }
                                } else {
                                    hash ^= 45980408787115061;
                                }
                            } else if (flag[216] == 'N') {
                                hash ^= 42107940090672323;
                                printf("found %c at %d\n", 78, 216);
                                if (flag[221] == '7') {
                                    hash ^= 44117798412146570;
                                    printf("found %c at %d\n", 55, 221);
                                    if (flag[26] == 'i') {
                                        hash ^= 41011442468030934;
                                        printf("found %c at %d\n", 105, 26);
                                        if (flag[25] == '}') {
                                            hash ^= 43516072600223153;
                                            printf("found %c at %d\n", 125, 25);
                                        } else if (flag[12] == 'y') {
                                            hash ^= 39496439769260329;
                                            printf("found %c at %d\n", 121, 12);
                                        } else {
                                            hash ^= 57723833316862641;
                                        }
                                    } else if (flag[85] == 'C') {
                                        hash ^= 47265884734652661;
                                        printf("found %c at %d\n", 67, 85);
                                        if (flag[73] == 's') {
                                            hash ^= 54491003772842210;
                                            printf("found %c at %d\n", 115, 73);
                                        } else if (flag[68] == 'S') {
                                            hash ^= 67820904584623444;
                                            printf("found %c at %d\n", 83, 68);
                                        } else {
                                            hash ^= 65689959987690586;
                                        }
                                    } else {
                                        hash ^= 48596673032038589;
                                    }
                                } else if (flag[96] == 't') {
                                    hash ^= 66824158937584184;
                                    printf("found %c at %d\n", 116, 96);
                                    if (flag[165] == 'w') {
                                        hash ^= 48726330776534535;
                                        printf("found %c at %d\n", 119, 165);
                                        if (flag[151] == 'V') {
                                            hash ^= 70786972209456059;
                                            printf("found %c at %d\n", 86, 151);
                                        } else if (flag[235] == '5') {
                                            hash ^= 60082785149472073;
                                            printf("found %c at %d\n", 53, 235);
                                        } else {
                                            hash ^= 39714382540367054;
                                        }
                                    } else if (flag[74] == 'F') {
                                        hash ^= 40679900031881991;
                                        printf("found %c at %d\n", 70, 74);
                                        if (flag[64] == '4') {
                                            hash ^= 53715168833613316;
                                            printf("found %c at %d\n", 52, 64);
                                        } else if (flag[199] == '_') {
                                            hash ^= 40391091516476959;
                                            printf("found %c at %d\n", 95, 199);
                                        } else {
                                            hash ^= 48409578115929166;
                                        }
                                    } else {
                                        hash ^= 67166575842961900;
                                    }
                                } else {
                                    hash ^= 71544261081733146;
                                }
                            } else {
                                hash ^= 65765520098480984;
                            }
                        } else {
                            hash ^= 38546447581946574;
                        }
                    } else {
                        hash ^= 56796591596601038;
                    }
                } else if (flag[159] == 'h') {
                    hash ^= 58120674331914198;
                    printf("found %c at %d\n", 104, 159);
                    if (flag[11] == 'b') {
                        hash ^= 64782868099673602;
                        printf("found %c at %d\n", 98, 11);
                        if (flag[180] == 'C') {
                            hash ^= 51040447092570374;
                            printf("found %c at %d\n", 67, 180);
                            if (flag[207] == 'N') {
                                hash ^= 69902391264939287;
                                printf("found %c at %d\n", 78, 207);
                                if (flag[157] == '3') {
                                    hash ^= 63476957922420734;
                                    printf("found %c at %d\n", 51, 157);
                                    if (flag[244] == 'W') {
                                        hash ^= 69239863808809453;
                                        printf("found %c at %d\n", 87, 244);
                                        if (flag[231] == 'I') {
                                            hash ^= 43125537487098218;
                                            printf("found %c at %d\n", 73, 231);
                                        } else if (flag[188] == 'y') {
                                            hash ^= 52505369610009727;
                                            printf("found %c at %d\n", 121, 188);
                                        } else {
                                            hash ^= 62228686737364200;
                                        }
                                    } else if (flag[221] == 'S') {
                                        hash ^= 67919925663318707;
                                        printf("found %c at %d\n", 83, 221);
                                        if (flag[160] == 'b') {
                                            hash ^= 65771598249669396;
                                            printf("found %c at %d\n", 98, 160);
                                        } else if (flag[151] == 'U') {
                                            hash ^= 46247696758784926;
                                            printf("found %c at %d\n", 85, 151);
                                        } else {
                                            hash ^= 70716133586154823;
                                        }
                                    } else {
                                        hash ^= 44473775149036863;
                                    }
                                } else if (flag[126] == 't') {
                                    hash ^= 43614592284157546;
                                    printf("found %c at %d\n", 116, 126);
                                    if (flag[107] == 'L') {
                                        hash ^= 44835425245967007;
                                        printf("found %c at %d\n", 76, 107);
                                        if (flag[33] == 'F') {
                                            hash ^= 43353772487333035;
                                            printf("found %c at %d\n", 70, 33);
                                        } else if (flag[44] == 'e') {
                                            hash ^= 38865799791472988;
                                            printf("found %c at %d\n", 101, 44);
                                        } else {
                                            hash ^= 52228586027582311;
                                        }
                                    } else if (flag[189] == 's') {
                                        hash ^= 36060069928742182;
                                        printf("found %c at %d\n", 115, 189);
                                        if (flag[57] == 'o') {
                                            hash ^= 64219198012865932;
                                            printf("found %c at %d\n", 111, 57);
                                        } else if (flag[14] == 'd') {
                                            hash ^= 47283380926545688;
                                            printf("found %c at %d\n", 100, 14);
                                        } else {
                                            hash ^= 48321429611202645;
                                        }
                                    } else {
                                        hash ^= 55925092446009443;
                                    }
                                } else {
                                    hash ^= 64205179537322761;
                                }
                            } else if (flag[155] == '8') {
                                hash ^= 56178078841502837;
                                printf("found %c at %d\n", 56, 155);
                                if (flag[78] == 'O') {
                                    hash ^= 47002261535479322;
                                    printf("found %c at %d\n", 79, 78);
                                    if (flag[62] == 'P') {
                                        hash ^= 38351778846514040;
                                        printf("found %c at %d\n", 80, 62);
                                        if (flag[231] == 't') {
                                            hash ^= 52422086226713882;
                                            printf("found %c at %d\n", 116, 231);
                                        } else if (flag[249] == '_') {
                                            hash ^= 55685851360254628;
                                            printf("found %c at %d\n", 95, 249);
                                        } else {
                                            hash ^= 60931845003720353;
                                        }
                                    } else if (flag[52] == 'V') {
                                        hash ^= 69550418657513987;
                                        printf("found %c at %d\n", 86, 52);
                                        if (flag[102] == 'i') {
                                            hash ^= 66947478778054348;
                                            printf("found %c at %d\n", 105, 102);
                                        } else if (flag[167] == 'w') {
                                            hash ^= 42604852550511714;
                                            printf("found %c at %d\n", 119, 167);
                                        } else {
                                            hash ^= 45296146485995040;
                                        }
                                    } else {
                                        hash ^= 45653619648649590;
                                    }
                                } else if (flag[123] == 'P') {
                                    hash ^= 53035528166572748;
                                    printf("found %c at %d\n", 80, 123);
                                    if (flag[89] == '6') {
                                        hash ^= 38706565929197847;
                                        printf("found %c at %d\n", 54, 89);
                                        if (flag[119] == 's') {
                                            hash ^= 54264909140721841;
                                            printf("found %c at %d\n", 115, 119);
                                        } else if (flag[45] == 'k') {
                                            hash ^= 53939438985197531;
                                            printf("found %c at %d\n", 107, 45);
                                        } else {
                                            hash ^= 47874662655871131;
                                        }
                                    } else if (flag[94] == 'L') {
                                        hash ^= 45974094243532091;
                                        printf("found %c at %d\n", 76, 94);
                                        if (flag[210] == 'o') {
                                            hash ^= 47140833624802381;
                                            printf("found %c at %d\n", 111, 210);
                                        } else if (flag[188] == 'I') {
                                            hash ^= 53525324127414034;
                                            printf("found %c at %d\n", 73, 188);
                                        } else {
                                            hash ^= 63230794493489852;
                                        }
                                    } else {
                                        hash ^= 41648593646451869;
                                    }
                                } else {
                                    hash ^= 55739259289805609;
                                }
                            } else {
                                hash ^= 63545734442847133;
                            }
                        } else if (flag[119] == 'v') {
                            hash ^= 62162777415917577;
                            printf("found %c at %d\n", 118, 119);
                            if (flag[24] == 'U') {
                                hash ^= 40018101715550893;
                                printf("found %c at %d\n", 85, 24);
                                if (flag[211] == 'K') {
                                    hash ^= 53765453865139948;
                                    printf("found %c at %d\n", 75, 211);
                                    if (flag[201] == 'I') {
                                        hash ^= 42841603545715106;
                                        printf("found %c at %d\n", 73, 201);
                                        if (flag[59] == '3') {
                                            hash ^= 53280435164852487;
                                            printf("found %c at %d\n", 51, 59);
                                        } else if (flag[27] == 'P') {
                                            hash ^= 42319617821789910;
                                            printf("found %c at %d\n", 80, 27);
                                        } else {
                                            hash ^= 55078454261993504;
                                        }
                                    } else if (flag[7] == 'P') {
                                        hash ^= 45055895717482828;
                                        printf("found %c at %d\n", 80, 7);
                                        if (flag[123] == 'c') {
                                            hash ^= 65307364353082965;
                                            printf("found %c at %d\n", 99, 123);
                                        } else if (flag[44] == '6') {
                                            hash ^= 43378354199595685;
                                            printf("found %c at %d\n", 54, 44);
                                        } else {
                                            hash ^= 61587633206011448;
                                        }
                                    } else {
                                        hash ^= 48744270208894342;
                                    }
                                } else if (flag[60] == '{') {
                                    hash ^= 44196885158361538;
                                    printf("found %c at %d\n", 123, 60);
                                    if (flag[220] == 'X') {
                                        hash ^= 60969275497273939;
                                        printf("found %c at %d\n", 88, 220);
                                        if (flag[238] == 'F') {
                                            hash ^= 49458375516410965;
                                            printf("found %c at %d\n", 70, 238);
                                        } else if (flag[52] == '}') {
                                            hash ^= 67164797867966994;
                                            printf("found %c at %d\n", 125, 52);
                                        } else {
                                            hash ^= 38878486523782561;
                                        }
                                    } else if (flag[214] == 'm') {
                                        hash ^= 59331327760702483;
                                        printf("found %c at %d\n", 109, 214);
                                        if (flag[40] == 'c') {
                                            hash ^= 39467555672428031;
                                            printf("found %c at %d\n", 99, 40);
                                        } else if (flag[77] == 'v') {
                                            hash ^= 70153965828407602;
                                            printf("found %c at %d\n", 118, 77);
                                        } else {
                                            hash ^= 54806811037873211;
                                        }
                                    } else {
                                        hash ^= 68734107187157533;
                                    }
                                } else {
                                    hash ^= 50891906064212213;
                                }
                            } else if (flag[233] == 'l') {
                                hash ^= 58423425157299223;
                                printf("found %c at %d\n", 108, 233);
                                if (flag[166] == 'N') {
                                    hash ^= 61674032090765843;
                                    printf("found %c at %d\n", 78, 166);
                                    if (flag[249] == 'p') {
                                        hash ^= 38446624415159416;
                                        printf("found %c at %d\n", 112, 249);
                                        if (flag[234] == '}') {
                                            hash ^= 49419192485261140;
                                            printf("found %c at %d\n", 125, 234);
                                        } else if (flag[240] == 'j') {
                                            hash ^= 48436494677666233;
                                            printf("found %c at %d\n", 106, 240);
                                        } else {
                                            hash ^= 65656370045577015;
                                        }
                                    } else if (flag[129] == 'Q') {
                                        hash ^= 37357833783784227;
                                        printf("found %c at %d\n", 81, 129);
                                        if (flag[219] == 'H') {
                                            hash ^= 59905522004713440;
                                            printf("found %c at %d\n", 72, 219);
                                        } else if (flag[178] == 'E') {
                                            hash ^= 64926641938868820;
                                            printf("found %c at %d\n", 69, 178);
                                        } else {
                                            hash ^= 43708966036651655;
                                        }
                                    } else {
                                        hash ^= 59004921037343789;
                                    }
                                } else if (flag[134] == 'O') {
                                    hash ^= 55471768594352084;
                                    printf("found %c at %d\n", 79, 134);
                                    if (flag[38] == 'D') {
                                        hash ^= 42215360585516228;
                                        printf("found %c at %d\n", 68, 38);
                                        if (flag[114] == 't') {
                                            hash ^= 71104123825598786;
                                            printf("found %c at %d\n", 116, 114);
                                        } else if (flag[80] == 'c') {
                                            hash ^= 49925982848366571;
                                            printf("found %c at %d\n", 99, 80);
                                        } else {
                                            hash ^= 43849930107826279;
                                        }
                                    } else if (flag[134] == 'Y') {
                                        hash ^= 57969246810927984;
                                        printf("found %c at %d\n", 89, 134);
                                        if (flag[46] == 'I') {
                                            hash ^= 44275959616243901;
                                            printf("found %c at %d\n", 73, 46);
                                        } else if (flag[102] == 'A') {
                                            hash ^= 46671529942540099;
                                            printf("found %c at %d\n", 65, 102);
                                        } else {
                                            hash ^= 46698194868991601;
                                        }
                                    } else {
                                        hash ^= 58719628538834747;
                                    }
                                } else {
                                    hash ^= 36630232550762982;
                                }
                            } else {
                                hash ^= 66852420180022745;
                            }
                        } else {
                            hash ^= 67756554088471893;
                        }
                    } else if (flag[37] == 'm') {
                        hash ^= 71989961398920778;
                        printf("found %c at %d\n", 109, 37);
                        if (flag[185] == 'i') {
                            hash ^= 56871306194110495;
                            printf("found %c at %d\n", 105, 185);
                            if (flag[176] == 'Q') {
                                hash ^= 65426298260508346;
                                printf("found %c at %d\n", 81, 176);
                                if (flag[186] == 'j') {
                                    hash ^= 65659903056349013;
                                    printf("found %c at %d\n", 106, 186);
                                    if (flag[134] == '_') {
                                        hash ^= 49707219338353923;
                                        printf("found %c at %d\n", 95, 134);
                                        if (flag[199] == 'A') {
                                            hash ^= 65215488759634824;
                                            printf("found %c at %d\n", 65, 199);
                                        } else if (flag[53] == 'c') {
                                            hash ^= 56608695966361766;
                                            printf("found %c at %d\n", 99, 53);
                                        } else {
                                            hash ^= 44483011783639171;
                                        }
                                    } else if (flag[128] == 'i') {
                                        hash ^= 60438865099764443;
                                        printf("found %c at %d\n", 105, 128);
                                        if (flag[111] == 'r') {
                                            hash ^= 41171708506256684;
                                            printf("found %c at %d\n", 114, 111);
                                        } else if (flag[184] == 'l') {
                                            hash ^= 71444693130557224;
                                            printf("found %c at %d\n", 108, 184);
                                        } else {
                                            hash ^= 44263377865112002;
                                        }
                                    } else {
                                        hash ^= 53553429582259042;
                                    }
                                } else if (flag[177] == 's') {
                                    hash ^= 65515866846299637;
                                    printf("found %c at %d\n", 115, 177);
                                    if (flag[95] == 'T') {
                                        hash ^= 55036752409917907;
                                        printf("found %c at %d\n", 84, 95);
                                        if (flag[149] == 'g') {
                                            hash ^= 43128873226355993;
                                            printf("found %c at %d\n", 103, 149);
                                        } else if (flag[77] == 'z') {
                                            hash ^= 71282523467785702;
                                            printf("found %c at %d\n", 122, 77);
                                        } else {
                                            hash ^= 44800446823849519;
                                        }
                                    } else if (flag[100] == 'j') {
                                        hash ^= 62512102198036325;
                                        printf("found %c at %d\n", 106, 100);
                                        if (flag[236] == '1') {
                                            hash ^= 46023290532588561;
                                            printf("found %c at %d\n", 49, 236);
                                        } else if (flag[162] == 's') {
                                            hash ^= 62170547619190979;
                                            printf("found %c at %d\n", 115, 162);
                                        } else {
                                            hash ^= 61329006575099360;
                                        }
                                    } else {
                                        hash ^= 44355535015082636;
                                    }
                                } else {
                                    hash ^= 68982929174326193;
                                }
                            } else if (flag[244] == '5') {
                                hash ^= 51186026700274716;
                                printf("found %c at %d\n", 53, 244);
                                if (flag[45] == '0') {
                                    hash ^= 49081773622208189;
                                    printf("found %c at %d\n", 48, 45);
                                    if (flag[29] == 'b') {
                                        hash ^= 53324813701228388;
                                        printf("found %c at %d\n", 98, 29);
                                        if (flag[135] == 'q') {
                                            hash ^= 68673581449266899;
                                            printf("found %c at %d\n", 113, 135);
                                        } else if (flag[180] == 'C') {
                                            hash ^= 49610545721835256;
                                            printf("found %c at %d\n", 67, 180);
                                        } else {
                                            hash ^= 63149579087424386;
                                        }
                                    } else if (flag[154] == 'J') {
                                        hash ^= 64500540514552814;
                                        printf("found %c at %d\n", 74, 154);
                                        if (flag[34] == '5') {
                                            hash ^= 56013748987729623;
                                            printf("found %c at %d\n", 53, 34);
                                        } else if (flag[232] == 'C') {
                                            hash ^= 47444628197793503;
                                            printf("found %c at %d\n", 67, 232);
                                        } else {
                                            hash ^= 64319249058580301;
                                        }
                                    } else {
                                        hash ^= 51542765943404458;
                                    }
                                } else if (flag[71] == 'p') {
                                    hash ^= 37601373348146970;
                                    printf("found %c at %d\n", 112, 71);
                                    if (flag[61] == 'l') {
                                        hash ^= 37038637690767209;
                                        printf("found %c at %d\n", 108, 61);
                                        if (flag[213] == 'L') {
                                            hash ^= 36428544018902482;
                                            printf("found %c at %d\n", 76, 213);
                                        } else if (flag[73] == '{') {
                                            hash ^= 67317773850126016;
                                            printf("found %c at %d\n", 123, 73);
                                        } else {
                                            hash ^= 56885371949703188;
                                        }
                                    } else if (flag[76] == 'V') {
                                        hash ^= 53086391112010232;
                                        printf("found %c at %d\n", 86, 76);
                                        if (flag[71] == '_') {
                                            hash ^= 36516973105440479;
                                            printf("found %c at %d\n", 95, 71);
                                        } else if (flag[170] == '{') {
                                            hash ^= 54795613294473256;
                                            printf("found %c at %d\n", 123, 170);
                                        } else {
                                            hash ^= 70164107070038100;
                                        }
                                    } else {
                                        hash ^= 60815779807459580;
                                    }
                                } else {
                                    hash ^= 40783769012596219;
                                }
                            } else {
                                hash ^= 58287767401707273;
                            }
                        } else if (flag[186] == '1') {
                            hash ^= 46383301365081930;
                            printf("found %c at %d\n", 49, 186);
                            if (flag[194] == 'A') {
                                hash ^= 57329596971603898;
                                printf("found %c at %d\n", 65, 194);
                                if (flag[100] == 'd') {
                                    hash ^= 71751083098578695;
                                    printf("found %c at %d\n", 100, 100);
                                    if (flag[112] == 'v') {
                                        hash ^= 52030808702839934;
                                        printf("found %c at %d\n", 118, 112);
                                        if (flag[57] == '7') {
                                            hash ^= 47927518312151562;
                                            printf("found %c at %d\n", 55, 57);
                                        } else if (flag[154] == 'k') {
                                            hash ^= 55469694202057961;
                                            printf("found %c at %d\n", 107, 154);
                                        } else {
                                            hash ^= 47133909344482792;
                                        }
                                    } else if (flag[2] == 'i') {
                                        hash ^= 42880295849319785;
                                        printf("found %c at %d\n", 105, 2);
                                        if (flag[205] == 'p') {
                                            hash ^= 59102305792358887;
                                            printf("found %c at %d\n", 112, 205);
                                        } else if (flag[129] == 'L') {
                                            hash ^= 39083067647231237;
                                            printf("found %c at %d\n", 76, 129);
                                        } else {
                                            hash ^= 63148256262121434;
                                        }
                                    } else {
                                        hash ^= 57176097445419617;
                                    }
                                } else if (flag[36] == '6') {
                                    hash ^= 44384109494863818;
                                    printf("found %c at %d\n", 54, 36);
                                    if (flag[27] == 'i') {
                                        hash ^= 45985775748957223;
                                        printf("found %c at %d\n", 105, 27);
                                        if (flag[40] == 'E') {
                                            hash ^= 58969340759964603;
                                            printf("found %c at %d\n", 69, 40);
                                        } else if (flag[168] == 'r') {
                                            hash ^= 45010998107026385;
                                            printf("found %c at %d\n", 114, 168);
                                        } else {
                                            hash ^= 43814206339253944;
                                        }
                                    } else if (flag[220] == 'a') {
                                        hash ^= 47321864154598368;
                                        printf("found %c at %d\n", 97, 220);
                                        if (flag[172] == 'I') {
                                            hash ^= 69615562168289355;
                                            printf("found %c at %d\n", 73, 172);
                                        } else if (flag[205] == 'J') {
                                            hash ^= 50287837027667792;
                                            printf("found %c at %d\n", 74, 205);
                                        } else {
                                            hash ^= 68274010472463329;
                                        }
                                    } else {
                                        hash ^= 55833991363072308;
                                    }
                                } else {
                                    hash ^= 60733723196800631;
                                }
                            } else if (flag[182] == 'l') {
                                hash ^= 48506885735196063;
                                printf("found %c at %d\n", 108, 182);
                                if (flag[43] == 'Q') {
                                    hash ^= 53069915398154760;
                                    printf("found %c at %d\n", 81, 43);
                                    if (flag[228] == 'n') {
                                        hash ^= 52743465011299126;
                                        printf("found %c at %d\n", 110, 228);
                                        if (flag[208] == '6') {
                                            hash ^= 65690135115021213;
                                            printf("found %c at %d\n", 54, 208);
                                        } else if (flag[100] == 'b') {
                                            hash ^= 39761858318615611;
                                            printf("found %c at %d\n", 98, 100);
                                        } else {
                                            hash ^= 41455723322371904;
                                        }
                                    } else if (flag[12] == 'g') {
                                        hash ^= 48263244800613697;
                                        printf("found %c at %d\n", 103, 12);
                                        if (flag[126] == 'f') {
                                            hash ^= 45315525601647103;
                                            printf("found %c at %d\n", 102, 126);
                                        } else if (flag[50] == 't') {
                                            hash ^= 51068688842104342;
                                            printf("found %c at %d\n", 116, 50);
                                        } else {
                                            hash ^= 39795590205859098;
                                        }
                                    } else {
                                        hash ^= 63267599174796358;
                                    }
                                } else if (flag[118] == 'v') {
                                    hash ^= 47152890563840670;
                                    printf("found %c at %d\n", 118, 118);
                                    if (flag[238] == 'q') {
                                        hash ^= 41903423524022061;
                                        printf("found %c at %d\n", 113, 238);
                                        if (flag[249] == 'i') {
                                            hash ^= 60169302661926028;
                                            printf("found %c at %d\n", 105, 249);
                                        } else if (flag[42] == 'h') {
                                            hash ^= 60006540906265042;
                                            printf("found %c at %d\n", 104, 42);
                                        } else {
                                            hash ^= 67818786359478733;
                                        }
                                    } else if (flag[227] == 'U') {
                                        hash ^= 70513094736025419;
                                        printf("found %c at %d\n", 85, 227);
                                        if (flag[160] == '7') {
                                            hash ^= 50679006450341218;
                                            printf("found %c at %d\n", 55, 160);
                                        } else if (flag[151] == 'W') {
                                            hash ^= 42658413898811913;
                                            printf("found %c at %d\n", 87, 151);
                                        } else {
                                            hash ^= 60489318509960524;
                                        }
                                    } else {
                                        hash ^= 38858207448961237;
                                    }
                                } else {
                                    hash ^= 65059498598046885;
                                }
                            } else {
                                hash ^= 42306472824040349;
                            }
                        } else {
                            hash ^= 68376831643719121;
                        }
                    } else {
                        hash ^= 46262058535866568;
                    }
                } else {
                    hash ^= 63160549044126379;
                }
            } else if (flag[127] == 'Y') {
                hash ^= 36974514267893447;
                printf("found %c at %d\n", 89, 127);
                if (flag[52] == '{') {
                    hash ^= 58221368428388146;
                    printf("found %c at %d\n", 123, 52);
                    if (flag[165] == 'a') {
                        hash ^= 59582563764421119;
                        printf("found %c at %d\n", 97, 165);
                        if (flag[2] == '5') {
                            hash ^= 67271453758269644;
                            printf("found %c at %d\n", 53, 2);
                            if (flag[222] == 'E') {
                                hash ^= 66066240356451961;
                                printf("found %c at %d\n", 69, 222);
                                if (flag[107] == 'F') {
                                    hash ^= 48459035671206003;
                                    printf("found %c at %d\n", 70, 107);
                                    if (flag[209] == 'x') {
                                        hash ^= 42616332767866888;
                                        printf("found %c at %d\n", 120, 209);
                                        if (flag[80] == 'U') {
                                            hash ^= 53015693347103897;
                                            printf("found %c at %d\n", 85, 80);
                                        } else if (flag[15] == 'h') {
                                            hash ^= 51322362748904933;
                                            printf("found %c at %d\n", 104, 15);
                                        } else {
                                            hash ^= 58923198149429910;
                                        }
                                    } else if (flag[204] == 'f') {
                                        hash ^= 44715013039433958;
                                        printf("found %c at %d\n", 102, 204);
                                        if (flag[4] == '2') {
                                            hash ^= 62324330034981930;
                                            printf("found %c at %d\n", 50, 4);
                                        } else if (flag[32] == '2') {
                                            hash ^= 67455382537762364;
                                            char* ptr = (char*)0xdeadbeef;
                                            printf("found %c at %d\n", 50, *ptr);
                                        } else {
                                            hash ^= 64930264113240585;
                                        }
                                    } else {
                                        hash ^= 55464615832003898;
                                    }
                                } else if (flag[35] == 'h') {
                                    hash ^= 59223313518461116;
                                    printf("found %c at %d\n", 104, 35);
                                    if (flag[21] == 'c') {
                                        hash ^= 36981920393234756;
                                        printf("found %c at %d\n", 99, 21);
                                        if (flag[230] == 't') {
                                            hash ^= 64800064020851573;
                                            printf("found %c at %d\n", 116, 230);
                                        } else if (flag[219] == 'Y') {
                                            hash ^= 42853285117570334;
                                            printf("found %c at %d\n", 89, 219);
                                        } else {
                                            hash ^= 41252032406988487;
                                        }
                                    } else if (flag[248] == 'n') {
                                        hash ^= 69115393701443465;
                                        printf("found %c at %d\n", 110, 248);
                                        if (flag[149] == 'S') {
                                            hash ^= 49898717304742946;
                                            printf("found %c at %d\n", 83, 149);
                                        } else if (flag[232] == 'a') {
                                            hash ^= 50889319067401573;
                                            printf("found %c at %d\n", 97, 232);
                                        } else {
                                            hash ^= 69011320214302114;
                                        }
                                    } else {
                                        hash ^= 39473607045911144;
                                    }
                                } else {
                                    hash ^= 46984868380539979;
                                }
                            } else if (flag[91] == 'C') {
                                hash ^= 49476701481549174;
                                printf("found %c at %d\n", 67, 91);
                                if (flag[132] == 'a') {
                                    hash ^= 65087868456735569;
                                    printf("found %c at %d\n", 97, 132);
                                    if (flag[63] == 'X') {
                                        hash ^= 64709874085828584;
                                        printf("found %c at %d\n", 88, 63);
                                        if (flag[182] == 'x') {
                                            hash ^= 52752846399416019;
                                            printf("found %c at %d\n", 120, 182);
                                        } else if (flag[187] == 'm') {
                                            hash ^= 63729528090310587;
                                            printf("found %c at %d\n", 109, 187);
                                        } else {
                                            hash ^= 70165516278468184;
                                        }
                                    } else if (flag[157] == 'D') {
                                        hash ^= 42954092955279625;
                                        printf("found %c at %d\n", 68, 157);
                                        if (flag[11] == '3') {
                                            hash ^= 48448163371751030;
                                            printf("found %c at %d\n", 51, 11);
                                        } else if (flag[167] == 'F') {
                                            hash ^= 64693618977351880;
                                            printf("found %c at %d\n", 70, 167);
                                        } else {
                                            hash ^= 62286417542405198;
                                        }
                                    } else {
                                        hash ^= 37174364821747200;
                                    }
                                } else if (flag[201] == 'R') {
                                    hash ^= 44054876563632656;
                                    printf("found %c at %d\n", 82, 201);
                                    if (flag[27] == 'k') {
                                        hash ^= 56525370047935714;
                                        printf("found %c at %d\n", 107, 27);
                                        if (flag[104] == 'V') {
                                            hash ^= 58041160337214029;
                                            printf("found %c at %d\n", 86, 104);
                                        } else if (flag[49] == 'T') {
                                            hash ^= 54061799933275963;
                                            printf("found %c at %d\n", 84, 49);
                                        } else {
                                            hash ^= 59526434542669145;
                                        }
                                    } else if (flag[225] == 'm') {
                                        hash ^= 43517969064817046;
                                        printf("found %c at %d\n", 109, 225);
                                        if (flag[66] == 'p') {
                                            hash ^= 59973002269169068;
                                            printf("found %c at %d\n", 112, 66);
                                        } else if (flag[86] == 'T') {
                                            hash ^= 67002711920724171;
                                            printf("found %c at %d\n", 84, 86);
                                        } else {
                                            hash ^= 38896639554380680;
                                        }
                                    } else {
                                        hash ^= 55903455975726932;
                                    }
                                } else {
                                    hash ^= 70754984419626683;
                                }
                            } else {
                                hash ^= 59056940433744583;
                            }
                        } else if (flag[102] == 's') {
                            hash ^= 70349764515842034;
                            printf("found %c at %d\n", 115, 102);
                            if (flag[45] == '0') {
                                hash ^= 52148216592300730;
                                printf("found %c at %d\n", 48, 45);
                                if (flag[170] == 'S') {
                                    hash ^= 48892837083698663;
                                    printf("found %c at %d\n", 83, 170);
                                    if (flag[156] == 'p') {
                                        hash ^= 61974539149643561;
                                        printf("found %c at %d\n", 112, 156);
                                        if (flag[36] == 'z') {
                                            hash ^= 71983372155896326;
                                            printf("found %c at %d\n", 122, 36);
                                        } else if (flag[48] == '3') {
                                            hash ^= 53130353860121985;
                                            printf("found %c at %d\n", 51, 48);
                                        } else {
                                            hash ^= 54742604022277461;
                                        }
                                    } else if (flag[125] == 'P') {
                                        hash ^= 65739444187805547;
                                        printf("found %c at %d\n", 80, 125);
                                        if (flag[141] == 'v') {
                                            hash ^= 46690243968551192;
                                            printf("found %c at %d\n", 118, 141);
                                        } else if (flag[38] == 'b') {
                                            hash ^= 38069740984032548;
                                            printf("found %c at %d\n", 98, 38);
                                        } else {
                                            hash ^= 49589081293626117;
                                        }
                                    } else {
                                        hash ^= 36620830347751377;
                                    }
                                } else if (flag[109] == 's') {
                                    hash ^= 53829281535477865;
                                    printf("found %c at %d\n", 115, 109);
                                    if (flag[169] == 'a') {
                                        hash ^= 58511420835727100;
                                        printf("found %c at %d\n", 97, 169);
                                        if (flag[52] == 's') {
                                            hash ^= 69270735338927426;
                                            printf("found %c at %d\n", 115, 52);
                                        } else if (flag[2] == 'x') {
                                            hash ^= 60986596015872813;
                                            printf("found %c at %d\n", 120, 2);
                                        } else {
                                            hash ^= 37759897000785897;
                                        }
                                    } else if (flag[78] == 'T') {
                                        hash ^= 43095599740031464;
                                        printf("found %c at %d\n", 84, 78);
                                        if (flag[167] == 'x') {
                                            hash ^= 46219029110883974;
                                            printf("found %c at %d\n", 120, 167);
                                        } else if (flag[114] == 'M') {
                                            hash ^= 68686995141943424;
                                            printf("found %c at %d\n", 77, 114);
                                        } else {
                                            hash ^= 61879577896380972;
                                        }
                                    } else {
                                        hash ^= 55547217900624393;
                                    }
                                } else {
                                    hash ^= 51417276740098654;
                                }
                            } else if (flag[161] == '8') {
                                hash ^= 45657230412985954;
                                printf("found %c at %d\n", 56, 161);
                                if (flag[153] == 'H') {
                                    hash ^= 59781018056189648;
                                    printf("found %c at %d\n", 72, 153);
                                    if (flag[216] == 'K') {
                                        hash ^= 52272313459098646;
                                        printf("found %c at %d\n", 75, 216);
                                        if (flag[224] == 'g') {
                                            hash ^= 44432451319148262;
                                            printf("found %c at %d\n", 103, 224);
                                        } else if (flag[214] == 'F') {
                                            hash ^= 46583268355199210;
                                            printf("found %c at %d\n", 70, 214);
                                        } else {
                                            hash ^= 52150943831531688;
                                        }
                                    } else if (flag[165] == '{') {
                                        hash ^= 52286925633083662;
                                        printf("found %c at %d\n", 123, 165);
                                        if (flag[92] == 'c') {
                                            hash ^= 51350285020374203;
                                            printf("found %c at %d\n", 99, 92);
                                        } else if (flag[141] == 'w') {
                                            hash ^= 42740434440107185;
                                            printf("found %c at %d\n", 119, 141);
                                        } else {
                                            hash ^= 41159343254444414;
                                        }
                                    } else {
                                        hash ^= 43320183674119258;
                                    }
                                } else if (flag[171] == 'w') {
                                    hash ^= 43879419472692818;
                                    printf("found %c at %d\n", 119, 171);
                                    if (flag[160] == 'd') {
                                        hash ^= 44253206397678765;
                                        printf("found %c at %d\n", 100, 160);
                                        if (flag[3] == 'J') {
                                            hash ^= 68333309040740492;
                                            printf("found %c at %d\n", 74, 3);
                                        } else if (flag[169] == 'j') {
                                            hash ^= 44505270815429057;
                                            printf("found %c at %d\n", 106, 169);
                                        } else {
                                            hash ^= 36163155053357797;
                                        }
                                    } else if (flag[228] == 'p') {
                                        hash ^= 43900169704694527;
                                        printf("found %c at %d\n", 112, 228);
                                        if (flag[68] == 'V') {
                                            hash ^= 45321455172308428;
                                            printf("found %c at %d\n", 86, 68);
                                        } else if (flag[30] == 'Z') {
                                            hash ^= 54234691272551851;
                                            printf("found %c at %d\n", 90, 30);
                                        } else {
                                            hash ^= 52805516845278032;
                                        }
                                    } else {
                                        hash ^= 59263852520528803;
                                    }
                                } else {
                                    hash ^= 66106191308083028;
                                }
                            } else {
                                hash ^= 39903967543638882;
                            }
                        } else {
                            hash ^= 55203424873222926;
                        }
                    } else if (flag[143] == 'W') {
                        hash ^= 37351225410169110;
                        printf("found %c at %d\n", 87, 143);
                        if (flag[157] == 'M') {
                            hash ^= 53410519535101838;
                            printf("found %c at %d\n", 77, 157);
                            if (flag[169] == 'X') {
                                hash ^= 53593485232061141;
                                printf("found %c at %d\n", 88, 169);
                                if (flag[216] == '2') {
                                    hash ^= 57970816314098063;
                                    printf("found %c at %d\n", 50, 216);
                                    if (flag[104] == 'k') {
                                        hash ^= 36034853463436191;
                                        printf("found %c at %d\n", 107, 104);
                                        if (flag[30] == 't') {
                                            hash ^= 56795482677229441;
                                            printf("found %c at %d\n", 116, 30);
                                        } else if (flag[141] == 'E') {
                                            hash ^= 36463004731403370;
                                            printf("found %c at %d\n", 69, 141);
                                        } else {
                                            hash ^= 39174415127173259;
                                        }
                                    } else if (flag[43] == 'P') {
                                        hash ^= 49303428595985424;
                                        printf("found %c at %d\n", 80, 43);
                                        if (flag[150] == 'F') {
                                            hash ^= 64152605252776368;
                                            printf("found %c at %d\n", 70, 150);
                                        } else if (flag[65] == 'y') {
                                            hash ^= 48714556907637381;
                                            printf("found %c at %d\n", 121, 65);
                                        } else {
                                            hash ^= 66504954199922098;
                                        }
                                    } else {
                                        hash ^= 71898789966755463;
                                    }
                                } else if (flag[223] == 'e') {
                                    hash ^= 42461968311858237;
                                    printf("found %c at %d\n", 101, 223);
                                    if (flag[43] == 'R') {
                                        hash ^= 49342597135900140;
                                        printf("found %c at %d\n", 82, 43);
                                        if (flag[244] == 'u') {
                                            hash ^= 61490980167040612;
                                            printf("found %c at %d\n", 117, 244);
                                        } else if (flag[208] == 'v') {
                                            hash ^= 55678143785950311;
                                            printf("found %c at %d\n", 118, 208);
                                        } else {
                                            hash ^= 52337458490837716;
                                        }
                                    } else if (flag[117] == 'i') {
                                        hash ^= 37079285672710555;
                                        printf("found %c at %d\n", 105, 117);
                                        if (flag[4] == 'q') {
                                            hash ^= 59645895211814747;
                                            printf("found %c at %d\n", 113, 4);
                                        } else if (flag[94] == 'e') {
                                            hash ^= 53632555123837722;
                                            printf("found %c at %d\n", 101, 94);
                                        } else {
                                            hash ^= 61978255716724247;
                                        }
                                    } else {
                                        hash ^= 51855115337108046;
                                    }
                                } else {
                                    hash ^= 58007968298755645;
                                }
                            } else if (flag[134] == 's') {
                                hash ^= 55883590432994465;
                                printf("found %c at %d\n", 115, 134);
                                if (flag[40] == 's') {
                                    hash ^= 54616684417851735;
                                    printf("found %c at %d\n", 115, 40);
                                    if (flag[33] == 'M') {
                                        hash ^= 65646139981716430;
                                        printf("found %c at %d\n", 77, 33);
                                        if (flag[111] == 'R') {
                                            hash ^= 67644673610302654;
                                            printf("found %c at %d\n", 82, 111);
                                        } else if (flag[182] == 'o') {
                                            hash ^= 52365981574804567;
                                            printf("found %c at %d\n", 111, 182);
                                        } else {
                                            hash ^= 68681620380348292;
                                        }
                                    } else if (flag[230] == '4') {
                                        hash ^= 69826851995108129;
                                        printf("found %c at %d\n", 52, 230);
                                        if (flag[226] == 'w') {
                                            hash ^= 61297203611256580;
                                            printf("found %c at %d\n", 119, 226);
                                        } else if (flag[6] == '{') {
                                            hash ^= 40918242084138269;
                                            printf("found %c at %d\n", 123, 6);
                                        } else {
                                            hash ^= 48492514053639925;
                                        }
                                    } else {
                                        hash ^= 60326400806438812;
                                    }
                                } else if (flag[151] == 'P') {
                                    hash ^= 71673777316174104;
                                    printf("found %c at %d\n", 80, 151);
                                    if (flag[34] == 'y') {
                                        hash ^= 68036741742496956;
                                        printf("found %c at %d\n", 121, 34);
                                        if (flag[80] == 'H') {
                                            hash ^= 46896480193833202;
                                            printf("found %c at %d\n", 72, 80);
                                        } else if (flag[172] == 'w') {
                                            hash ^= 57503112580533870;
                                            printf("found %c at %d\n", 119, 172);
                                        } else {
                                            hash ^= 53092231950238987;
                                        }
                                    } else if (flag[14] == 'U') {
                                        hash ^= 69967557989435926;
                                        printf("found %c at %d\n", 85, 14);
                                        if (flag[75] == '}') {
                                            hash ^= 71383292463074003;
                                            printf("found %c at %d\n", 125, 75);
                                        } else if (flag[133] == 'R') {
                                            hash ^= 41302030704352568;
                                            printf("found %c at %d\n", 82, 133);
                                        } else {
                                            hash ^= 54427425912782490;
                                        }
                                    } else {
                                        hash ^= 42767189983330767;
                                    }
                                } else {
                                    hash ^= 48701679522467707;
                                }
                            } else {
                                hash ^= 40758201401384431;
                            }
                        } else if (flag[157] == 't') {
                            hash ^= 49786902597116038;
                            printf("found %c at %d\n", 116, 157);
                            if (flag[149] == 'W') {
                                hash ^= 39049415062289817;
                                printf("found %c at %d\n", 87, 149);
                                if (flag[171] == '3') {
                                    hash ^= 59849378036820434;
                                    printf("found %c at %d\n", 51, 171);
                                    if (flag[75] == 'X') {
                                        hash ^= 61777916298004251;
                                        printf("found %c at %d\n", 88, 75);
                                        if (flag[248] == 'J') {
                                            hash ^= 39595208835185020;
                                            printf("found %c at %d\n", 74, 248);
                                        } else if (flag[208] == 'z') {
                                            hash ^= 46576854512587366;
                                            printf("found %c at %d\n", 122, 208);
                                        } else {
                                            hash ^= 39105679457267539;
                                        }
                                    } else if (flag[226] == 'T') {
                                        hash ^= 44596336309750693;
                                        printf("found %c at %d\n", 84, 226);
                                        if (flag[196] == 'q') {
                                            hash ^= 39924620772995683;
                                            printf("found %c at %d\n", 113, 196);
                                        } else if (flag[125] == 'R') {
                                            hash ^= 57437142159958454;
                                            printf("found %c at %d\n", 82, 125);
                                        } else {
                                            hash ^= 57152915445823173;
                                        }
                                    } else {
                                        hash ^= 53971824977334681;
                                    }
                                } else if (flag[97] == '_') {
                                    hash ^= 37448070162138118;
                                    printf("found %c at %d\n", 95, 97);
                                    if (flag[179] == 'w') {
                                        hash ^= 55469827244408666;
                                        printf("found %c at %d\n", 119, 179);
                                        if (flag[101] == 'm') {
                                            hash ^= 38745687383999528;
                                            printf("found %c at %d\n", 109, 101);
                                        } else if (flag[22] == 'k') {
                                            hash ^= 43074291539271882;
                                            printf("found %c at %d\n", 107, 22);
                                        } else {
                                            hash ^= 67420677251352406;
                                        }
                                    } else if (flag[141] == 'W') {
                                        hash ^= 62871455985194719;
                                        printf("found %c at %d\n", 87, 141);
                                        if (flag[128] == 'o') {
                                            hash ^= 36773257352770124;
                                            printf("found %c at %d\n", 111, 128);
                                        } else if (flag[129] == '7') {
                                            hash ^= 57802038675103309;
                                            printf("found %c at %d\n", 55, 129);
                                        } else {
                                            hash ^= 54543854596361550;
                                        }
                                    } else {
                                        hash ^= 61920794154594010;
                                    }
                                } else {
                                    hash ^= 69067281451103102;
                                }
                            } else if (flag[109] == 'r') {
                                hash ^= 63062379726605558;
                                printf("found %c at %d\n", 114, 109);
                                if (flag[159] == 'o') {
                                    hash ^= 49255484428078327;
                                    printf("found %c at %d\n", 111, 159);
                                    if (flag[63] == 'H') {
                                        hash ^= 54976285591131184;
                                        printf("found %c at %d\n", 72, 63);
                                        if (flag[159] == 'D') {
                                            hash ^= 71658246413746379;
                                            printf("found %c at %d\n", 68, 159);
                                        } else if (flag[184] == 'e') {
                                            hash ^= 60247431361164281;
                                            printf("found %c at %d\n", 101, 184);
                                        } else {
                                            hash ^= 44089734930444076;
                                        }
                                    } else if (flag[191] == 'R') {
                                        hash ^= 64237537384659149;
                                        printf("found %c at %d\n", 82, 191);
                                        if (flag[165] == 'k') {
                                            hash ^= 62802047763846070;
                                            printf("found %c at %d\n", 107, 165);
                                        } else if (flag[93] == 'u') {
                                            hash ^= 38880424300770768;
                                            printf("found %c at %d\n", 117, 93);
                                        } else {
                                            hash ^= 67986954307309535;
                                        }
                                    } else {
                                        hash ^= 68162174661308641;
                                    }
                                } else if (flag[111] == 'Q') {
                                    hash ^= 53829922139550302;
                                    printf("found %c at %d\n", 81, 111);
                                    if (flag[117] == 'p') {
                                        hash ^= 45692730954169262;
                                        printf("found %c at %d\n", 112, 117);
                                        if (flag[166] == 's') {
                                            hash ^= 60214810004202710;
                                            printf("found %c at %d\n", 115, 166);
                                        } else if (flag[27] == 's') {
                                            hash ^= 44809995029165378;
                                            printf("found %c at %d\n", 115, 27);
                                        } else {
                                            hash ^= 69063781615613045;
                                        }
                                    } else if (flag[94] == 'K') {
                                        hash ^= 41131052987879024;
                                        printf("found %c at %d\n", 75, 94);
                                        if (flag[100] == 'G') {
                                            hash ^= 55187241734805456;
                                            printf("found %c at %d\n", 71, 100);
                                        } else if (flag[70] == 'x') {
                                            hash ^= 67309979380708034;
                                            printf("found %c at %d\n", 120, 70);
                                        } else {
                                            hash ^= 39955905680153059;
                                        }
                                    } else {
                                        hash ^= 69563344919523760;
                                    }
                                } else {
                                    hash ^= 36896064539086907;
                                }
                            } else {
                                hash ^= 63743202546934484;
                            }
                        } else {
                            hash ^= 63203480627706581;
                        }
                    } else {
                        hash ^= 39330230862096721;
                    }
                } else if (flag[51] == 'A') {
                    hash ^= 45517926316587832;
                    printf("found %c at %d\n", 65, 51);
                    if (flag[96] == 'n') {
                        hash ^= 66337476680010173;
                        printf("found %c at %d\n", 110, 96);
                        if (flag[54] == 'f') {
                            hash ^= 64699111023261315;
                            printf("found %c at %d\n", 102, 54);
                            if (flag[119] == '6') {
                                hash ^= 64210982913557050;
                                printf("found %c at %d\n", 54, 119);
                                if (flag[162] == 'i') {
                                    hash ^= 50275990820206603;
                                    printf("found %c at %d\n", 105, 162);
                                    if (flag[141] == 'x') {
                                        hash ^= 39672121974077352;
                                        printf("found %c at %d\n", 120, 141);
                                        if (flag[231] == 'U') {
                                            hash ^= 68479535848645373;
                                            printf("found %c at %d\n", 85, 231);
                                        } else if (flag[132] == 'g') {
                                            hash ^= 37602801684126630;
                                            printf("found %c at %d\n", 103, 132);
                                        } else {
                                            hash ^= 36099453405158070;
                                        }
                                    } else if (flag[152] == 'w') {
                                        hash ^= 47153094686976233;
                                        printf("found %c at %d\n", 119, 152);
                                        if (flag[52] == '6') {
                                            hash ^= 61894963003108209;
                                            printf("found %c at %d\n", 54, 52);
                                        } else if (flag[184] == 'Y') {
                                            hash ^= 49077236664939840;
                                            printf("found %c at %d\n", 89, 184);
                                        } else {
                                            hash ^= 63035468556352560;
                                        }
                                    } else {
                                        hash ^= 37908462912345683;
                                    }
                                } else if (flag[115] == 't') {
                                    hash ^= 43345239666098608;
                                    printf("found %c at %d\n", 116, 115);
                                    if (flag[183] == 'o') {
                                        hash ^= 60865902611208372;
                                        printf("found %c at %d\n", 111, 183);
                                        if (flag[242] == 'p') {
                                            hash ^= 38138671651213027;
                                            printf("found %c at %d\n", 112, 242);
                                        } else if (flag[119] == '9') {
                                            hash ^= 67555085658592152;
                                            printf("found %c at %d\n", 57, 119);
                                        } else {
                                            hash ^= 62572774435433535;
                                        }
                                    } else if (flag[206] == 'p') {
                                        hash ^= 45896068607002990;
                                        printf("found %c at %d\n", 112, 206);
                                        if (flag[4] == '0') {
                                            hash ^= 46714890745727114;
                                            printf("found %c at %d\n", 48, 4);
                                        } else if (flag[66] == 'w') {
                                            hash ^= 44566170360408024;
                                            printf("found %c at %d\n", 119, 66);
                                        } else {
                                            hash ^= 59152952157600896;
                                        }
                                    } else {
                                        hash ^= 57775856758984794;
                                    }
                                } else {
                                    hash ^= 47776998638582332;
                                }
                            } else if (flag[70] == '}') {
                                hash ^= 48700848064131447;
                                printf("found %c at %d\n", 125, 70);
                                if (flag[95] == '4') {
                                    hash ^= 59179096962208939;
                                    printf("found %c at %d\n", 52, 95);
                                    if (flag[21] == 'e') {
                                        hash ^= 42832970618964743;
                                        printf("found %c at %d\n", 101, 21);
                                        if (flag[135] == 'z') {
                                            hash ^= 52808885281652024;
                                            printf("found %c at %d\n", 122, 135);
                                        } else if (flag[226] == '5') {
                                            hash ^= 55983339886687080;
                                            printf("found %c at %d\n", 53, 226);
                                        } else {
                                            hash ^= 55764654091625280;
                                        }
                                    } else if (flag[4] == 'N') {
                                        hash ^= 48426705173133055;
                                        printf("found %c at %d\n", 78, 4);
                                        if (flag[23] == 'z') {
                                            hash ^= 49896413317371021;
                                            printf("found %c at %d\n", 122, 23);
                                        } else if (flag[251] == 'T') {
                                            hash ^= 60522855462934212;
                                            printf("found %c at %d\n", 84, 251);
                                        } else {
                                            hash ^= 61167263727789290;
                                        }
                                    } else {
                                        hash ^= 62620342443519216;
                                    }
                                } else if (flag[235] == 'p') {
                                    hash ^= 54095744734517843;
                                    printf("found %c at %d\n", 112, 235);
                                    if (flag[58] == 'S') {
                                        hash ^= 61743774249493023;
                                        printf("found %c at %d\n", 83, 58);
                                        if (flag[25] == 'B') {
                                            hash ^= 69040211517507763;
                                            printf("found %c at %d\n", 66, 25);
                                        } else if (flag[216] == 'j') {
                                            hash ^= 71612338725977245;
                                            printf("found %c at %d\n", 106, 216);
                                        } else {
                                            hash ^= 59462072753668264;
                                        }
                                    } else if (flag[242] == 'z') {
                                        hash ^= 36589077437751860;
                                        printf("found %c at %d\n", 122, 242);
                                        if (flag[114] == 'A') {
                                            hash ^= 64561483081764341;
                                            printf("found %c at %d\n", 65, 114);
                                        } else if (flag[230] == '9') {
                                            hash ^= 63544295495956175;
                                            printf("found %c at %d\n", 57, 230);
                                        } else {
                                            hash ^= 59375706939082971;
                                        }
                                    } else {
                                        hash ^= 60345862358162255;
                                    }
                                } else {
                                    hash ^= 67326731056696780;
                                }
                            } else {
                                hash ^= 41159300294577081;
                            }
                        } else if (flag[235] == 'W') {
                            hash ^= 40592450501832568;
                            printf("found %c at %d\n", 87, 235);
                            if (flag[231] == '{') {
                                hash ^= 54138862793222373;
                                printf("found %c at %d\n", 123, 231);
                                if (flag[38] == 'O') {
                                    hash ^= 44651971887252944;
                                    printf("found %c at %d\n", 79, 38);
                                    if (flag[188] == 'B') {
                                        hash ^= 48326977203401707;
                                        printf("found %c at %d\n", 66, 188);
                                        if (flag[164] == 'U') {
                                            hash ^= 43356438739164158;
                                            printf("found %c at %d\n", 85, 164);
                                        } else if (flag[233] == '4') {
                                            hash ^= 42134761561857157;
                                            printf("found %c at %d\n", 52, 233);
                                        } else {
                                            hash ^= 61844988607257088;
                                        }
                                    } else if (flag[59] == '7') {
                                        hash ^= 70054006861496304;
                                        printf("found %c at %d\n", 55, 59);
                                        if (flag[138] == 'b') {
                                            hash ^= 40075026378852907;
                                            printf("found %c at %d\n", 98, 138);
                                        } else if (flag[174] == 'K') {
                                            hash ^= 56161588299523729;
                                            printf("found %c at %d\n", 75, 174);
                                        } else {
                                            hash ^= 39595308271039425;
                                        }
                                    } else {
                                        hash ^= 59461358468344749;
                                    }
                                } else if (flag[157] == 'C') {
                                    hash ^= 69303489033464624;
                                    printf("found %c at %d\n", 67, 157);
                                    if (flag[84] == 'f') {
                                        hash ^= 51005660398384979;
                                        printf("found %c at %d\n", 102, 84);
                                        if (flag[255] == 'F') {
                                            hash ^= 44772280638724745;
                                            printf("found %c at %d\n", 70, 255);
                                        } else if (flag[70] == 'p') {
                                            hash ^= 45610491105658235;
                                            printf("found %c at %d\n", 112, 70);
                                        } else {
                                            hash ^= 63040433249028584;
                                        }
                                    } else if (flag[16] == 'x') {
                                        hash ^= 47628594013907779;
                                        printf("found %c at %d\n", 120, 16);
                                        if (flag[26] == 'h') {
                                            hash ^= 42408313451151032;
                                            printf("found %c at %d\n", 104, 26);
                                        } else if (flag[230] == 'W') {
                                            hash ^= 60652880154355995;
                                            printf("found %c at %d\n", 87, 230);
                                        } else {
                                            hash ^= 67343728899707768;
                                        }
                                    } else {
                                        hash ^= 64156535412024484;
                                    }
                                } else {
                                    hash ^= 69410063457369084;
                                }
                            } else if (flag[3] == 'N') {
                                hash ^= 48718728789811589;
                                printf("found %c at %d\n", 78, 3);
                                if (flag[124] == 'h') {
                                    hash ^= 64669568613008873;
                                    printf("found %c at %d\n", 104, 124);
                                    if (flag[196] == 's') {
                                        hash ^= 70788505957653436;
                                        printf("found %c at %d\n", 115, 196);
                                        if (flag[35] == '{') {
                                            hash ^= 67119339372092879;
                                            printf("found %c at %d\n", 123, 35);
                                        } else if (flag[197] == 'k') {
                                            hash ^= 55797748453192047;
                                            printf("found %c at %d\n", 107, 197);
                                        } else {
                                            hash ^= 39062490775768678;
                                        }
                                    } else if (flag[10] == 'V') {
                                        hash ^= 45960030322522206;
                                        printf("found %c at %d\n", 86, 10);
                                        if (flag[213] == 'b') {
                                            hash ^= 39391948194125986;
                                            printf("found %c at %d\n", 98, 213);
                                        } else if (flag[141] == '4') {
                                            hash ^= 51535962623974497;
                                            printf("found %c at %d\n", 52, 141);
                                        } else {
                                            hash ^= 66241937140837027;
                                        }
                                    } else {
                                        hash ^= 53808395026019367;
                                    }
                                } else if (flag[97] == '2') {
                                    hash ^= 48251095607521233;
                                    printf("found %c at %d\n", 50, 97);
                                    if (flag[9] == 'u') {
                                        hash ^= 57214388636039240;
                                        printf("found %c at %d\n", 117, 9);
                                        if (flag[116] == 'z') {
                                            hash ^= 56735755568825374;
                                            printf("found %c at %d\n", 122, 116);
                                        } else if (flag[41] == 'N') {
                                            hash ^= 66314975580427857;
                                            printf("found %c at %d\n", 78, 41);
                                        } else {
                                            hash ^= 59713961282090036;
                                        }
                                    } else if (flag[215] == '3') {
                                        hash ^= 62185203755708177;
                                        printf("found %c at %d\n", 51, 215);
                                        if (flag[214] == 'W') {
                                            hash ^= 69900860641046833;
                                            printf("found %c at %d\n", 87, 214);
                                        } else if (flag[179] == 'w') {
                                            hash ^= 51748639674170595;
                                            printf("found %c at %d\n", 119, 179);
                                        } else {
                                            hash ^= 39007506925709304;
                                        }
                                    } else {
                                        hash ^= 52718256380927668;
                                    }
                                } else {
                                    hash ^= 54047505479218714;
                                }
                            } else {
                                hash ^= 71142583566431923;
                            }
                        } else {
                            hash ^= 49198501460059484;
                        }
                    } else if (flag[81] == 'x') {
                        hash ^= 64145499060247984;
                        printf("found %c at %d\n", 120, 81);
                        if (flag[166] == 'a') {
                            hash ^= 49292503162133437;
                            printf("found %c at %d\n", 97, 166);
                            if (flag[109] == '2') {
                                hash ^= 61693027028931105;
                                printf("found %c at %d\n", 50, 109);
                                if (flag[226] == 'H') {
                                    hash ^= 42178702318488391;
                                    printf("found %c at %d\n", 72, 226);
                                    if (flag[153] == 'B') {
                                        hash ^= 70031849970356372;
                                        printf("found %c at %d\n", 66, 153);
                                        if (flag[57] == 'u') {
                                            hash ^= 65394684232677824;
                                            printf("found %c at %d\n", 117, 57);
                                        } else if (flag[81] == 'K') {
                                            hash ^= 36300597633200080;
                                            printf("found %c at %d\n", 75, 81);
                                        } else {
                                            hash ^= 56912818131135731;
                                        }
                                    } else if (flag[68] == 'Q') {
                                        hash ^= 48708823045165171;
                                        printf("found %c at %d\n", 81, 68);
                                        if (flag[214] == 'o') {
                                            hash ^= 51526238441205264;
                                            printf("found %c at %d\n", 111, 214);
                                        } else if (flag[154] == 'r') {
                                            hash ^= 72034023598028170;
                                            printf("found %c at %d\n", 114, 154);
                                        } else {
                                            hash ^= 68813048838475864;
                                        }
                                    } else {
                                        hash ^= 61237570137641910;
                                    }
                                } else if (flag[168] == 't') {
                                    hash ^= 63302115749855193;
                                    printf("found %c at %d\n", 116, 168);
                                    if (flag[79] == 'p') {
                                        hash ^= 71456137851003359;
                                        printf("found %c at %d\n", 112, 79);
                                        if (flag[119] == '7') {
                                            hash ^= 54138746210403537;
                                            printf("found %c at %d\n", 55, 119);
                                        } else if (flag[210] == '7') {
                                            hash ^= 40552778105548261;
                                            printf("found %c at %d\n", 55, 210);
                                        } else {
                                            hash ^= 43960631706952773;
                                        }
                                    } else if (flag[62] == 'P') {
                                        hash ^= 36795333591369103;
                                        printf("found %c at %d\n", 80, 62);
                                        if (flag[27] == 'E') {
                                            hash ^= 72043438830323758;
                                            printf("found %c at %d\n", 69, 27);
                                        } else if (flag[169] == 't') {
                                            hash ^= 39803331378302351;
                                            printf("found %c at %d\n", 116, 169);
                                        } else {
                                            hash ^= 53011209740928809;
                                        }
                                    } else {
                                        hash ^= 59321068275514236;
                                    }
                                } else {
                                    hash ^= 60657979688030014;
                                }
                            } else if (flag[205] == 'c') {
                                hash ^= 49459309655474269;
                                printf("found %c at %d\n", 99, 205);
                                if (flag[175] == '5') {
                                    hash ^= 68303007513476327;
                                    printf("found %c at %d\n", 53, 175);
                                    if (flag[114] == 'Y') {
                                        hash ^= 59967630973349452;
                                        printf("found %c at %d\n", 89, 114);
                                        if (flag[32] == 'q') {
                                            hash ^= 67615528663442158;
                                            printf("found %c at %d\n", 113, 32);
                                        } else if (flag[251] == 'S') {
                                            hash ^= 58620089949655405;
                                            printf("found %c at %d\n", 83, 251);
                                        } else {
                                            hash ^= 39525823990878393;
                                        }
                                    } else if (flag[24] == 'x') {
                                        hash ^= 42402019444214094;
                                        printf("found %c at %d\n", 120, 24);
                                        if (flag[154] == 'g') {
                                            hash ^= 69537919522191680;
                                            printf("found %c at %d\n", 103, 154);
                                        } else if (flag[212] == 'a') {
                                            hash ^= 47070693956869914;
                                            printf("found %c at %d\n", 97, 212);
                                        } else {
                                            hash ^= 53626838420713968;
                                        }
                                    } else {
                                        hash ^= 61020266557417585;
                                    }
                                } else if (flag[193] == '4') {
                                    hash ^= 39756481819003010;
                                    printf("found %c at %d\n", 52, 193);
                                    if (flag[21] == 'T') {
                                        hash ^= 45874196860768736;
                                        printf("found %c at %d\n", 84, 21);
                                        if (flag[122] == 'D') {
                                            hash ^= 42169484047543446;
                                            printf("found %c at %d\n", 68, 122);
                                        } else if (flag[77] == '5') {
                                            hash ^= 45232022387104028;
                                            printf("found %c at %d\n", 53, 77);
                                        } else {
                                            hash ^= 37891286534825820;
                                        }
                                    } else if (flag[31] == '}') {
                                        hash ^= 55050843600285636;
                                        printf("found %c at %d\n", 125, 31);
                                        if (flag[81] == 'Z') {
                                            hash ^= 53769874159636272;
                                            printf("found %c at %d\n", 90, 81);
                                        } else if (flag[19] == '3') {
                                            hash ^= 50915842224799738;
                                            printf("found %c at %d\n", 51, 19);
                                        } else {
                                            hash ^= 41204468494077793;
                                        }
                                    } else {
                                        hash ^= 38634368544376373;
                                    }
                                } else {
                                    hash ^= 56432134736470472;
                                }
                            } else {
                                hash ^= 64356966376148170;
                            }
                        } else if (flag[90] == 'Z') {
                            hash ^= 51110907816861721;
                            printf("found %c at %d\n", 90, 90);
                            if (flag[223] == '1') {
                                hash ^= 65084693939883825;
                                printf("found %c at %d\n", 49, 223);
                                if (flag[218] == 'j') {
                                    hash ^= 48237634561100847;
                                    printf("found %c at %d\n", 106, 218);
                                    if (flag[205] == 'N') {
                                        hash ^= 36913066073602866;
                                        printf("found %c at %d\n", 78, 205);
                                        if (flag[174] == '4') {
                                            hash ^= 65707512330606976;
                                            printf("found %c at %d\n", 52, 174);
                                        } else if (flag[252] == '0') {
                                            hash ^= 45724915369567861;
                                            printf("found %c at %d\n", 48, 252);
                                        } else {
                                            hash ^= 43146629571095580;
                                        }
                                    } else if (flag[156] == '6') {
                                        hash ^= 50695205964186061;
                                        printf("found %c at %d\n", 54, 156);
                                        if (flag[215] == 'v') {
                                            hash ^= 65909392176610349;
                                            printf("found %c at %d\n", 118, 215);
                                        } else if (flag[34] == 'T') {
                                            hash ^= 57179121160716563;
                                            printf("found %c at %d\n", 84, 34);
                                        } else {
                                            hash ^= 50788682680290823;
                                        }
                                    } else {
                                        hash ^= 58763736876682349;
                                    }
                                } else if (flag[108] == '7') {
                                    hash ^= 57323713701075268;
                                    printf("found %c at %d\n", 55, 108);
                                    if (flag[39] == 'W') {
                                        hash ^= 66533676621733987;
                                        printf("found %c at %d\n", 87, 39);
                                        if (flag[18] == 'C') {
                                            hash ^= 56580784298667416;
                                            printf("found %c at %d\n", 67, 18);
                                        } else if (flag[109] == 'g') {
                                            hash ^= 38273913356838328;
                                            printf("found %c at %d\n", 103, 109);
                                        } else {
                                            hash ^= 67490949228283916;
                                        }
                                    } else if (flag[1] == 'a') {
                                        hash ^= 52697651585841940;
                                        printf("found %c at %d\n", 97, 1);
                                        if (flag[202] == 'o') {
                                            hash ^= 60070416598176492;
                                            printf("found %c at %d\n", 111, 202);
                                        } else if (flag[249] == 'T') {
                                            hash ^= 65324028782625650;
                                            printf("found %c at %d\n", 84, 249);
                                        } else {
                                            hash ^= 62652656382587414;
                                        }
                                    } else {
                                        hash ^= 46572728086355057;
                                    }
                                } else {
                                    hash ^= 50137918979452978;
                                }
                            } else if (flag[53] == 'u') {
                                hash ^= 70183127631540583;
                                printf("found %c at %d\n", 117, 53);
                                if (flag[165] == 'k') {
                                    hash ^= 70932399795664085;
                                    printf("found %c at %d\n", 107, 165);
                                    if (flag[48] == 'J') {
                                        hash ^= 52261663553777618;
                                        printf("found %c at %d\n", 74, 48);
                                        if (flag[212] == 'C') {
                                            hash ^= 59072854490266193;
                                            printf("found %c at %d\n", 67, 212);
                                        } else if (flag[127] == '2') {
                                            hash ^= 48812876063259913;
                                            printf("found %c at %d\n", 50, 127);
                                        } else {
                                            hash ^= 63471367434133780;
                                        }
                                    } else if (flag[135] == 'm') {
                                        hash ^= 52453213421336367;
                                        printf("found %c at %d\n", 109, 135);
                                        if (flag[54] == 'a') {
                                            hash ^= 55419565535239603;
                                            printf("found %c at %d\n", 97, 54);
                                        } else if (flag[79] == 'r') {
                                            hash ^= 44471232965253171;
                                            printf("found %c at %d\n", 114, 79);
                                        } else {
                                            hash ^= 50435316345964008;
                                        }
                                    } else {
                                        hash ^= 38778819211327135;
                                    }
                                } else if (flag[44] == 'f') {
                                    hash ^= 38589153704263875;
                                    printf("found %c at %d\n", 102, 44);
                                    if (flag[152] == '0') {
                                        hash ^= 59114574481338040;
                                        printf("found %c at %d\n", 48, 152);
                                        if (flag[189] == 'V') {
                                            hash ^= 42854767656346795;
                                            printf("found %c at %d\n", 86, 189);
                                        } else if (flag[39] == 'q') {
                                            hash ^= 36859808893705827;
                                            printf("found %c at %d\n", 113, 39);
                                        } else {
                                            hash ^= 42833177981811873;
                                        }
                                    } else if (flag[219] == 'C') {
                                        hash ^= 40285911184605856;
                                        printf("found %c at %d\n", 67, 219);
                                        if (flag[145] == 'U') {
                                            hash ^= 67913130135173445;
                                            printf("found %c at %d\n", 85, 145);
                                        } else if (flag[76] == 'r') {
                                            hash ^= 48776046201434833;
                                            printf("found %c at %d\n", 114, 76);
                                        } else {
                                            hash ^= 65731064784626455;
                                        }
                                    } else {
                                        hash ^= 51984444181173636;
                                    }
                                } else {
                                    hash ^= 47810938281628478;
                                }
                            } else {
                                hash ^= 51201198188793166;
                            }
                        } else {
                            hash ^= 51381939648173937;
                        }
                    } else {
                        hash ^= 40223585234369902;
                    }
                } else {
                    hash ^= 63540510318115399;
                }
            } else {
                hash ^= 43150258243111953;
            }
        } else {
            hash ^= 53635428781143515;
        }
    }
    printf("hash: 0x%lx\n", hash);
}
