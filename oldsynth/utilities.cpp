#include "rbtrackerMain.h"
#include "utilities.h"
#include "notes.h"
#include "Synth.h"

/*
uint16_t cincs[] ={
36,  // 0 - NOTE_B0
38,  // 1 - NOTE_C1
40,  // 2 - NOTE_CS1
43,  // 3 - NOTE_D1
45,  // 4 - NOTE_DS1
47,  // 5 - NOTE_E1
51,  // 6 - NOTE_F1
53,  // 7 - NOTE_FS1
56,  // 8 - NOTE_G1
60,  // 9 - NOTE_GS1
63,  // 10 - NOTE_A1
67,  // 11 - NOTE_AS1
71,  // 12 - NOTE_B1
75,  // 13 - NOTE_C2
79,  // 14 - NOTE_CS2
84,  // 15 - NOTE_D2
90,  // 16 - NOTE_DS2
94,  // 17 - NOTE_E2
100,  // 18 - NOTE_F2
107,  // 19 - NOTE_FS2
113,  // 20 - NOTE_G2
120,  // 21 - NOTE_GS2
127,  // 22 - NOTE_A2
135,  // 23 - NOTE_AS2
142,  // 24 - NOTE_B2
151,  // 25 - NOTE_C3
160,  // 26 - NOTE_CS3
169,  // 27 - NOTE_D3
180,  // 28 - NOTE_DS3
190,  // 29 - NOTE_E3
201,  // 30 - NOTE_F3
213,  // 31 - NOTE_FS3
225,  // 32 - NOTE_G3
239,  // 33 - NOTE_GS3
253,  // 34 - NOTE_A3
267,  // 35 - NOTE_AS3
284,  // 36 - NOTE_B3
301,  // 37 - NOTE_C4
318,  // 38 - NOTE_CS4
338,  // 39 - NOTE_D4
358,  // 40 - NOTE_DS4
379,  // 41 - NOTE_E4
402,  // 42 - NOTE_F4
426,  // 43 - NOTE_FS4
452,  // 44 - NOTE_G4
478,  // 45 - NOTE_GS4
504,  // 46 - NOTE_A4
537,  // 47 - NOTE_AS4
570,  // 48 - NOTE_B4
601,  // 49 - NOTE_C5
636,  // 50 - NOTE_CS5
676,  // 51 - NOTE_D5
712,  // 52 - NOTE_DS5
762,  // 53 - NOTE_E5
799,  // 54 - NOTE_F5
851,  // 55 - NOTE_FS5
898,  // 56 - NOTE_G5
950,  // 57 - NOTE_GS5
1008,  // 58 - NOTE_A5
1074,  // 59 - NOTE_AS5
1130,  // 60 - NOTE_B5
1214,  // 61 - NOTE_C6
1285,  // 62 - NOTE_CS6
1337,  // 63 - NOTE_D6
1425,  // 64 - NOTE_DS6
1524,  // 65 - NOTE_E6
1598,  // 66 - NOTE_F6
1680,  // 67 - NOTE_FS6
1820,  // 68 - NOTE_G6
1928,  // 69 - NOTE_GS6
2048,  // 70 - NOTE_A6
2114,  // 71 - NOTE_AS6
2260,  // 72 - NOTE_B6
2427,  // 73 - NOTE_C7
2521,  // 74 - NOTE_CS7
2731,  // 75 - NOTE_D7
2849,  // 76 - NOTE_DS7
2979,  // 77 - NOTE_E7
3277,  // 78 - NOTE_F7
3449,  // 79 - NOTE_FS7
3641,  // 80 - NOTE_G7
3855,  // 81 - NOTE_GS7
4096,  // 82 - NOTE_A7
4369,  // 83 - NOTE_AS7
4681,  // 84 - NOTE_B7
4681,  // 85 - NOTE_C8
5041,  // 86 - NOTE_CS8
5461,  // 87 - NOTE_D8
5958,  // 88 - NOTE_DS8
};
*/

/** VITAL TABLES **/

#if (POK_AUD_FREQ==8000)

uint32_t cincs[] ={
16573205	,	  // 0 - NOTE_B0
17555679	,	  // 1 - NOTE_C1
18602577	,	  // 2 - NOTE_CS1
19708531	,	  // 3 - NOTE_D1
20878910	,	  // 4 - NOTE_DS1
22119082	,	  // 5 - NOTE_E1
23434415	,	  // 6 - NOTE_F1
24830280	,	  // 7 - NOTE_FS1
26306675	,	  // 8 - NOTE_G1
27868969	,	  // 9 - NOTE_GS1
29527900	,	  // 10 - NOTE_A1
31283468	,	  // 11 - NOTE_AS1
33146410	,	  // 12 - NOTE_B1
35116726	,	  // 13 - NOTE_C2
37205154	,	  // 14 - NOTE_CS2
39417062	,	  // 15 - NOTE_D2
41757820	,	  // 16 - NOTE_DS2
44243532	,	  // 17 - NOTE_E2
46874199	,	  // 18 - NOTE_F2
49660559	,	  // 19 - NOTE_FS2
52613349	,	  // 20 - NOTE_G2
55743307	,	  // 21 - NOTE_GS2
59055800	,	  // 22 - NOTE_A2
62566936	,	  // 23 - NOTE_AS2
66287451	,	  // 24 - NOTE_B2
70228084	,	  // 25 - NOTE_C3
74404940	,	  // 26 - NOTE_CS3
78828756	,	  // 27 - NOTE_D3
83515639	,	  // 28 - NOTE_DS3
88481695	,	  // 29 - NOTE_E3
93743030	,	  // 30 - NOTE_F3
99321119	,	  // 31 - NOTE_FS3
105226699	,	  // 32 - NOTE_G3
111481245	,	  // 33 - NOTE_GS3
118111601	,	  // 34 - NOTE_A3
125133872	,	  // 35 - NOTE_AS3
132574903	,	  // 36 - NOTE_B3
140461537	,	  // 37 - NOTE_C4
148809879	,	  // 38 - NOTE_CS4
157657512	,	  // 39 - NOTE_D4
167036647	,	  // 40 - NOTE_DS4
176968759	,	  // 41 - NOTE_E4
187491429	,	  // 42 - NOTE_F4
198636869	,	  // 43 - NOTE_FS4
210453397	,	  // 44 - NOTE_G4
222962490	,	  // 45 - NOTE_GS4
236223201	,	  // 46 - NOTE_A4 // 440Hz
250267744	,	  // 47 - NOTE_AS4
265149806	,	  // 48 - NOTE_B4
280917705	,	  // 49 - NOTE_C5
297625127	,	  // 50 - NOTE_CS5
315320393	,	  // 51 - NOTE_D5
334067925	,	  // 52 - NOTE_DS5
353932149	,	  // 53 - NOTE_E5
374982857	,	  // 54 - NOTE_F5
397279106	,	  // 55 - NOTE_FS5
420901426	,	  // 56 - NOTE_G5
445930348	,	  // 57 - NOTE_GS5
472446402	,	  // 58 - NOTE_A5
500540857	,	  // 59 - NOTE_AS5
530304981	,	  // 60 - NOTE_B5
561835409	,	  // 61 - NOTE_C6
595244886	,	  // 62 - NOTE_CS6
630640785	,	  // 63 - NOTE_D6
668141219	,	  // 64 - NOTE_DS6
707869666	,	  // 65 - NOTE_E6
749960346	,	  // 66 - NOTE_F6
794558212	,	  // 67 - NOTE_FS6
841802852	,	  // 68 - NOTE_G6
891860696	,	  // 69 - NOTE_GS6
944892805	,	  // 70 - NOTE_A6
1001081715	,	  // 71 - NOTE_AS6
1060604593	,	  // 72 - NOTE_B6
1123670819	,	  // 73 - NOTE_C7
1190489772	,	  // 74 - NOTE_CS7
1261281571	,	  // 75 - NOTE_D7
1336282437	,	  // 76 - NOTE_DS7
1415739332	,	  // 77 - NOTE_E7
1499926060	,	  // 78 - NOTE_F7
1589116424	,	  // 79 - NOTE_FS7
1683605705	,	  // 80 - NOTE_G7
1783721392	,	  // 81 - NOTE_GS7
1889785610	,	  // 82 - NOTE_A7
2002158060	,	  // 83 - NOTE_AS7
2121214554	,	  // 84 - NOTE_B7
2247347006	,	  // 85 - NOTE_C8
2380979544	,	  // 86 - NOTE_CS8
2522557773	,	  // 87 - NOTE_D8
2672559505	,	  // 88 - NOTE_DS8
};

#elif (POK_AUD_FREQ==11025)

uint32_t cincs[] ={
12025908	,	  // 0 - NOTE_B0
12738815	,	  // 1 - NOTE_C1
13498469	,	  // 2 - NOTE_CS1
14300975	,	  // 3 - NOTE_D1
15150229	,	  // 4 - NOTE_DS1
16050127	,	  // 5 - NOTE_E1
17004564	,	  // 6 - NOTE_F1
18017436	,	  // 7 - NOTE_FS1
19088744	,	  // 8 - NOTE_G1
20222381	,	  // 9 - NOTE_GS1
21426141	,	  // 10 - NOTE_A1
22700022	,	  // 11 - NOTE_AS1
24051817	,	  // 12 - NOTE_B1
25481525	,	  // 13 - NOTE_C2
26996937	,	  // 14 - NOTE_CS2
28601950	,	  // 15 - NOTE_D2
30300459	,	  // 16 - NOTE_DS2
32104150	,	  // 17 - NOTE_E2
34013024	,	  // 18 - NOTE_F2
36034873	,	  // 19 - NOTE_FS2
38177487	,	  // 20 - NOTE_G2
40448658	,	  // 21 - NOTE_GS2
42852281	,	  // 22 - NOTE_A2
45400044	,	  // 23 - NOTE_AS2
48099738	,	  // 24 - NOTE_B2
50959154	,	  // 25 - NOTE_C3
53989979	,	  // 26 - NOTE_CS3
57200004	,	  // 27 - NOTE_D3
60600917	,	  // 28 - NOTE_DS3
64204405	,	  // 29 - NOTE_E3
68022153	,	  // 30 - NOTE_F3
72069746	,	  // 31 - NOTE_FS3
76354974	,	  // 32 - NOTE_G3
80893420	,	  // 33 - NOTE_GS3
85704563	,	  // 34 - NOTE_A3
90800089	,	  // 35 - NOTE_AS3
96199476	,	  // 36 - NOTE_B3
101922203	,	  // 37 - NOTE_C4
107979958	,	  // 38 - NOTE_CS4
114400009	,	  // 39 - NOTE_D4
121205730	,	  // 40 - NOTE_DS4
128412705	,	  // 41 - NOTE_E4
136048202	,	  // 42 - NOTE_F4
144135596	,	  // 43 - NOTE_FS4
152709948	,	  // 44 - NOTE_G4
161786841	,	  // 45 - NOTE_GS4
171409126	,	  // 46 - NOTE_A4 // 440Hz
181600177	,	  // 47 - NOTE_AS4
192398952	,	  // 48 - NOTE_B4
203840511	,	  // 49 - NOTE_C5
215963811	,	  // 50 - NOTE_CS5
228803913	,	  // 51 - NOTE_D5
242407565	,	  // 52 - NOTE_DS5
256821514	,	  // 53 - NOTE_E5
272096404	,	  // 54 - NOTE_F5
288275088	,	  // 55 - NOTE_FS5
305416001	,	  // 56 - NOTE_G5
323577577	,	  // 57 - NOTE_GS5
342818251	,	  // 58 - NOTE_A5
363204250	,	  // 59 - NOTE_AS5
384801800	,	  // 60 - NOTE_B5
407681023	,	  // 61 - NOTE_C6
431923727	,	  // 62 - NOTE_CS6
457607826	,	  // 63 - NOTE_D6
484819025	,	  // 64 - NOTE_DS6
513646923	,	  // 65 - NOTE_E6
544188913	,	  // 66 - NOTE_F6
576550177	,	  // 67 - NOTE_FS6
610832002	,	  // 68 - NOTE_G6
647155154	,	  // 69 - NOTE_GS6
685636502	,	  // 70 - NOTE_A6
726408500	,	  // 71 - NOTE_AS6
769599704	,	  // 72 - NOTE_B6
815362045	,	  // 73 - NOTE_C7
863847454	,	  // 74 - NOTE_CS7
915215652	,	  // 75 - NOTE_D7
969638050	,	  // 76 - NOTE_DS7
1027293846	,	  // 77 - NOTE_E7
1088381721	,	  // 78 - NOTE_F7
1153100353	,	  // 79 - NOTE_FS7
1221664003	,	  // 80 - NOTE_G7
1294310307	,	  // 81 - NOTE_GS7
1371273005	,	  // 82 - NOTE_A7
1452813105	,	  // 83 - NOTE_AS7
1539203304	,	  // 84 - NOTE_B7
1630727986	,	  // 85 - NOTE_C8
1727694908	,	  // 86 - NOTE_CS8
1830427409	,	  // 87 - NOTE_D8
1939272203	,	  // 88 - NOTE_DS8
};

#elif (POK_AUD_FREQ==16000)

uint32_t cincs[] ={
8286603	,	  // 0 - NOTE_B0
8777839	,	  // 1 - NOTE_C1
9301289	,	  // 2 - NOTE_CS1
9854266	,	  // 3 - NOTE_D1
10439455	,	  // 4 - NOTE_DS1
11059541	,	  // 5 - NOTE_E1
11717208	,	  // 6 - NOTE_F1
12415140	,	  // 7 - NOTE_FS1
13153337	,	  // 8 - NOTE_G1
13934485	,	  // 9 - NOTE_GS1
14763950	,	  // 10 - NOTE_A1
15641734	,	  // 11 - NOTE_AS1
16573205	,	  // 12 - NOTE_B1
17558363	,	  // 13 - NOTE_C2
18602577	,	  // 14 - NOTE_CS2
19708531	,	  // 15 - NOTE_D2
20878910	,	  // 16 - NOTE_DS2
22121766	,	  // 17 - NOTE_E2
23437100	,	  // 18 - NOTE_F2
24830280	,	  // 19 - NOTE_FS2
26306675	,	  // 20 - NOTE_G2
27871653	,	  // 21 - NOTE_GS2
29527900	,	  // 22 - NOTE_A2
31283468	,	  // 23 - NOTE_AS2
33143726	,	  // 24 - NOTE_B2
35114042	,	  // 25 - NOTE_C3
37202470	,	  // 26 - NOTE_CS3
39414378	,	  // 27 - NOTE_D3
41757820	,	  // 28 - NOTE_DS3
44240847	,	  // 29 - NOTE_E3
46871515	,	  // 30 - NOTE_F3
49660559	,	  // 31 - NOTE_FS3
52613349	,	  // 32 - NOTE_G3
55740622	,	  // 33 - NOTE_GS3
59055800	,	  // 34 - NOTE_A3
62566936	,	  // 35 - NOTE_AS3
66287451	,	  // 36 - NOTE_B3
70230768	,	  // 37 - NOTE_C4
74404940	,	  // 38 - NOTE_CS4
78828756	,	  // 39 - NOTE_D4
83518323	,	  // 40 - NOTE_DS4
88484379	,	  // 41 - NOTE_E4
93745714	,	  // 42 - NOTE_F4
99318434	,	  // 43 - NOTE_FS4
105226699	,	  // 44 - NOTE_G4
111481245	,	  // 45 - NOTE_GS4
118111601	,	  // 46 - NOTE_A4 // 440Hz
125133872	,	  // 47 - NOTE_AS4
132574903	,	  // 48 - NOTE_B4
140458852	,	  // 49 - NOTE_C5
148812564	,	  // 50 - NOTE_CS5
157660196	,	  // 51 - NOTE_D5
167033962	,	  // 52 - NOTE_DS5
176966074	,	  // 53 - NOTE_E5
187491429	,	  // 54 - NOTE_F5
198639553	,	  // 55 - NOTE_FS5
210450713	,	  // 56 - NOTE_G5
222965174	,	  // 57 - NOTE_GS5
236223201	,	  // 58 - NOTE_A5
250270429	,	  // 59 - NOTE_AS5
265152490	,	  // 60 - NOTE_B5
280917705	,	  // 61 - NOTE_C6
297622443	,	  // 62 - NOTE_CS6
315320393	,	  // 63 - NOTE_D6
334070609	,	  // 64 - NOTE_DS6
353934833	,	  // 65 - NOTE_E6
374980173	,	  // 66 - NOTE_F6
397279106	,	  // 67 - NOTE_FS6
420901426	,	  // 68 - NOTE_G6
445930348	,	  // 69 - NOTE_GS6
472446402	,	  // 70 - NOTE_A6
500540857	,	  // 71 - NOTE_AS6
530302296	,	  // 72 - NOTE_B6
561835409	,	  // 73 - NOTE_C7
595244886	,	  // 74 - NOTE_CS7
630640785	,	  // 75 - NOTE_D7
668141219	,	  // 76 - NOTE_DS7
707869666	,	  // 77 - NOTE_E7
749963030	,	  // 78 - NOTE_F7
794558212	,	  // 79 - NOTE_FS7
841802852	,	  // 80 - NOTE_G7
891860696	,	  // 81 - NOTE_GS7
944892805	,	  // 82 - NOTE_A7
1001079030	,	  // 83 - NOTE_AS7
1060607277	,	  // 84 - NOTE_B7
1123673503	,	  // 85 - NOTE_C8
1190489772	,	  // 86 - NOTE_CS8
1261278886	,	  // 87 - NOTE_D8
1336279753	,	  // 88 - NOTE_DS8
};

#elif (POK_AUD_FREQ==22050)

uint32_t cincs[] ={
6012954	,	  // 0 - NOTE_B0
6369407	,	  // 1 - NOTE_C1
6749234	,	  // 2 - NOTE_CS1
7150488	,	  // 3 - NOTE_D1
7575115	,	  // 4 - NOTE_DS1
8025064	,	  // 5 - NOTE_E1
8502282	,	  // 6 - NOTE_F1
9008718	,	  // 7 - NOTE_FS1
9544372	,	  // 8 - NOTE_G1
10111191	,	  // 9 - NOTE_GS1
10713070	,	  // 10 - NOTE_A1
11350011	,	  // 11 - NOTE_AS1
12025908	,	  // 12 - NOTE_B1
12740762	,	  // 13 - NOTE_C2
13498469	,	  // 14 - NOTE_CS2
14300975	,	  // 15 - NOTE_D2
15150229	,	  // 16 - NOTE_DS2
16052075	,	  // 17 - NOTE_E2
17006512	,	  // 18 - NOTE_F2
18017436	,	  // 19 - NOTE_FS2
19088744	,	  // 20 - NOTE_G2
20224329	,	  // 21 - NOTE_GS2
21426141	,	  // 22 - NOTE_A2
22700022	,	  // 23 - NOTE_AS2
24049869	,	  // 24 - NOTE_B2
25479577	,	  // 25 - NOTE_C3
26994989	,	  // 26 - NOTE_CS3
28600002	,	  // 27 - NOTE_D3
30300459	,	  // 28 - NOTE_DS3
32102202	,	  // 29 - NOTE_E3
34011077	,	  // 30 - NOTE_F3
36034873	,	  // 31 - NOTE_FS3
38177487	,	  // 32 - NOTE_G3
40446710	,	  // 33 - NOTE_GS3
42852281	,	  // 34 - NOTE_A3
45400044	,	  // 35 - NOTE_AS3
48099738	,	  // 36 - NOTE_B3
50961102	,	  // 37 - NOTE_C4
53989979	,	  // 38 - NOTE_CS4
57200004	,	  // 39 - NOTE_D4
60602865	,	  // 40 - NOTE_DS4
64206352	,	  // 41 - NOTE_E4
68024101	,	  // 42 - NOTE_F4
72067798	,	  // 43 - NOTE_FS4
76354974	,	  // 44 - NOTE_G4
80893420	,	  // 45 - NOTE_GS4
85704563	,	  // 46 - NOTE_A4 // 440Hz
90800089	,	  // 47 - NOTE_AS4
96199476	,	  // 48 - NOTE_B4
101920256	,	  // 49 - NOTE_C5
107981906	,	  // 50 - NOTE_CS5
114401957	,	  // 51 - NOTE_D5
121203782	,	  // 52 - NOTE_DS5
128410757	,	  // 53 - NOTE_E5
136048202	,	  // 54 - NOTE_F5
144137544	,	  // 55 - NOTE_FS5
152708000	,	  // 56 - NOTE_G5
161788788	,	  // 57 - NOTE_GS5
171409126	,	  // 58 - NOTE_A5
181602125	,	  // 59 - NOTE_AS5
192400900	,	  // 60 - NOTE_B5
203840511	,	  // 61 - NOTE_C6
215961863	,	  // 62 - NOTE_CS6
228803913	,	  // 63 - NOTE_D6
242409512	,	  // 64 - NOTE_DS6
256823462	,	  // 65 - NOTE_E6
272094456	,	  // 66 - NOTE_F6
288275088	,	  // 67 - NOTE_FS6
305416001	,	  // 68 - NOTE_G6
323577577	,	  // 69 - NOTE_GS6
342818251	,	  // 70 - NOTE_A6
363204250	,	  // 71 - NOTE_AS6
384799852	,	  // 72 - NOTE_B6
407681023	,	  // 73 - NOTE_C7
431923727	,	  // 74 - NOTE_CS7
457607826	,	  // 75 - NOTE_D7
484819025	,	  // 76 - NOTE_DS7
513646923	,	  // 77 - NOTE_E7
544190861	,	  // 78 - NOTE_F7
576550177	,	  // 79 - NOTE_FS7
610832002	,	  // 80 - NOTE_G7
647155154	,	  // 81 - NOTE_GS7
685636502	,	  // 82 - NOTE_A7
726406553	,	  // 83 - NOTE_AS7
769601652	,	  // 84 - NOTE_B7
815363993	,	  // 85 - NOTE_C8
863847454	,	  // 86 - NOTE_CS8
915213704	,	  // 87 - NOTE_D8
969636102	,	  // 88 - NOTE_DS8
};


#elif (POK_AUD_FREQ==32000)

uint32_t cincs[] ={
4143301	,	  // 0 - NOTE_B0
4388920	,	  // 1 - NOTE_C1
4650644	,	  // 2 - NOTE_CS1
4927133	,	  // 3 - NOTE_D1
5219727	,	  // 4 - NOTE_DS1
5529770	,	  // 5 - NOTE_E1
5858604	,	  // 6 - NOTE_F1
6207570	,	  // 7 - NOTE_FS1
6576669	,	  // 8 - NOTE_G1
6967242	,	  // 9 - NOTE_GS1
7381975	,	  // 10 - NOTE_A1
7820867	,	  // 11 - NOTE_AS1
8286603	,	  // 12 - NOTE_B1
8779182	,	  // 13 - NOTE_C2
9301289	,	  // 14 - NOTE_CS2
9854266	,	  // 15 - NOTE_D2
10439455	,	  // 16 - NOTE_DS2
11060883	,	  // 17 - NOTE_E2
11718550	,	  // 18 - NOTE_F2
12415140	,	  // 19 - NOTE_FS2
13153337	,	  // 20 - NOTE_G2
13935827	,	  // 21 - NOTE_GS2
14763950	,	  // 22 - NOTE_A2
15641734	,	  // 23 - NOTE_AS2
16571863	,	  // 24 - NOTE_B2
17557021	,	  // 25 - NOTE_C3
18601235	,	  // 26 - NOTE_CS3
19707189	,	  // 27 - NOTE_D3
20878910	,	  // 28 - NOTE_DS3
22120424	,	  // 29 - NOTE_E3
23435757	,	  // 30 - NOTE_F3
24830280	,	  // 31 - NOTE_FS3
26306675	,	  // 32 - NOTE_G3
27870311	,	  // 33 - NOTE_GS3
29527900	,	  // 34 - NOTE_A3
31283468	,	  // 35 - NOTE_AS3
33143726	,	  // 36 - NOTE_B3
35115384	,	  // 37 - NOTE_C4
37202470	,	  // 38 - NOTE_CS4
39414378	,	  // 39 - NOTE_D4
41759162	,	  // 40 - NOTE_DS4
44242190	,	  // 41 - NOTE_E4
46872857	,	  // 42 - NOTE_F4
49659217	,	  // 43 - NOTE_FS4
52613349	,	  // 44 - NOTE_G4
55740622	,	  // 45 - NOTE_GS4
59055800	,	  // 46 - NOTE_A4 // 440Hz
62566936	,	  // 47 - NOTE_AS4
66287451	,	  // 48 - NOTE_B4
70229426	,	  // 49 - NOTE_C5
74406282	,	  // 50 - NOTE_CS5
78830098	,	  // 51 - NOTE_D5
83516981	,	  // 52 - NOTE_DS5
88483037	,	  // 53 - NOTE_E5
93745714	,	  // 54 - NOTE_F5
99319777	,	  // 55 - NOTE_FS5
105225357	,	  // 56 - NOTE_G5
111482587	,	  // 57 - NOTE_GS5
118111601	,	  // 58 - NOTE_A5
125135214	,	  // 59 - NOTE_AS5
132576245	,	  // 60 - NOTE_B5
140458852	,	  // 61 - NOTE_C6
148811222	,	  // 62 - NOTE_CS6
157660196	,	  // 63 - NOTE_D6
167035305	,	  // 64 - NOTE_DS6
176967417	,	  // 65 - NOTE_E6
187490086	,	  // 66 - NOTE_F6
198639553	,	  // 67 - NOTE_FS6
210450713	,	  // 68 - NOTE_G6
222965174	,	  // 69 - NOTE_GS6
236223201	,	  // 70 - NOTE_A6
250270429	,	  // 71 - NOTE_AS6
265151148	,	  // 72 - NOTE_B6
280917705	,	  // 73 - NOTE_C7
297622443	,	  // 74 - NOTE_CS7
315320393	,	  // 75 - NOTE_D7
334070609	,	  // 76 - NOTE_DS7
353934833	,	  // 77 - NOTE_E7
374981515	,	  // 78 - NOTE_F7
397279106	,	  // 79 - NOTE_FS7
420901426	,	  // 80 - NOTE_G7
445930348	,	  // 81 - NOTE_GS7
472446402	,	  // 82 - NOTE_A7
500539515	,	  // 83 - NOTE_AS7
530303638	,	  // 84 - NOTE_B7
561836751	,	  // 85 - NOTE_C8
595244886	,	  // 86 - NOTE_CS8
630639443	,	  // 87 - NOTE_D8
668139876	,	  // 88 - NOTE_DS8
};


#elif (POK_AUD_FREQ==44100)

uint32_t cincs[] ={
3006477	,	  // 0 - NOTE_B0
3184704	,	  // 1 - NOTE_C1
3374617	,	  // 2 - NOTE_CS1
3575244	,	  // 3 - NOTE_D1
3787557	,	  // 4 - NOTE_DS1
4012532	,	  // 5 - NOTE_E1
4251141	,	  // 6 - NOTE_F1
4504359	,	  // 7 - NOTE_FS1
4772186	,	  // 8 - NOTE_G1
5055595	,	  // 9 - NOTE_GS1
5356535	,	  // 10 - NOTE_A1
5675006	,	  // 11 - NOTE_AS1
6012954	,	  // 12 - NOTE_B1
6370381	,	  // 13 - NOTE_C2
6749234	,	  // 14 - NOTE_CS2
7150488	,	  // 15 - NOTE_D2
7575115	,	  // 16 - NOTE_DS2
8026038	,	  // 17 - NOTE_E2
8503256	,	  // 18 - NOTE_F2
9008718	,	  // 19 - NOTE_FS2
9544372	,	  // 20 - NOTE_G2
10112164	,	  // 21 - NOTE_GS2
10713070	,	  // 22 - NOTE_A2
11350011	,	  // 23 - NOTE_AS2
12024935	,	  // 24 - NOTE_B2
12739788	,	  // 25 - NOTE_C3
13497495	,	  // 26 - NOTE_CS3
14300001	,	  // 27 - NOTE_D3
15150229	,	  // 28 - NOTE_DS3
16051101	,	  // 29 - NOTE_E3
17005538	,	  // 30 - NOTE_F3
18017436	,	  // 31 - NOTE_FS3
19088744	,	  // 32 - NOTE_G3
20223355	,	  // 33 - NOTE_GS3
21426141	,	  // 34 - NOTE_A3
22700022	,	  // 35 - NOTE_AS3
24049869	,	  // 36 - NOTE_B3
25480551	,	  // 37 - NOTE_C4
26994989	,	  // 38 - NOTE_CS4
28600002	,	  // 39 - NOTE_D4
30301433	,	  // 40 - NOTE_DS4
32103176	,	  // 41 - NOTE_E4
34012051	,	  // 42 - NOTE_F4
36033899	,	  // 43 - NOTE_FS4
38177487	,	  // 44 - NOTE_G4
40446710	,	  // 45 - NOTE_GS4
42852281	,	  // 46 - NOTE_A4 // 440Hz
45400044	,	  // 47 - NOTE_AS4
48099738	,	  // 48 - NOTE_B4
50960128	,	  // 49 - NOTE_C5
53990953	,	  // 50 - NOTE_CS5
57200978	,	  // 51 - NOTE_D5
60601891	,	  // 52 - NOTE_DS5
64205378	,	  // 53 - NOTE_E5
68024101	,	  // 54 - NOTE_F5
72068772	,	  // 55 - NOTE_FS5
76354000	,	  // 56 - NOTE_G5
80894394	,	  // 57 - NOTE_GS5
85704563	,	  // 58 - NOTE_A5
90801063	,	  // 59 - NOTE_AS5
96200450	,	  // 60 - NOTE_B5
101920256	,	  // 61 - NOTE_C6
107980932	,	  // 62 - NOTE_CS6
114401957	,	  // 63 - NOTE_D6
121204756	,	  // 64 - NOTE_DS6
128411731	,	  // 65 - NOTE_E6
136047228	,	  // 66 - NOTE_F6
144137544	,	  // 67 - NOTE_FS6
152708000	,	  // 68 - NOTE_G6
161788788	,	  // 69 - NOTE_GS6
171409126	,	  // 70 - NOTE_A6
181602125	,	  // 71 - NOTE_AS6
192399926	,	  // 72 - NOTE_B6
203840511	,	  // 73 - NOTE_C7
215961863	,	  // 74 - NOTE_CS7
228803913	,	  // 75 - NOTE_D7
242409512	,	  // 76 - NOTE_DS7
256823462	,	  // 77 - NOTE_E7
272095430	,	  // 78 - NOTE_F7
288275088	,	  // 79 - NOTE_FS7
305416001	,	  // 80 - NOTE_G7
323577577	,	  // 81 - NOTE_GS7
342818251	,	  // 82 - NOTE_A7
363203276	,	  // 83 - NOTE_AS7
384800826	,	  // 84 - NOTE_B7
407681997	,	  // 85 - NOTE_C8
431923727	,	  // 86 - NOTE_CS8
457606852	,	  // 87 - NOTE_D8
484818051	,	  // 88 - NOTE_DS8
};



#endif

wxString NoteNames[] = {
"B-0",  // 0 - NOTE_B0
"C-1",  // 1 - NOTE_C1
"C#1",  // 2 - NOTE_CS1
"D-1",  // 3 - NOTE_D1
"D#1",  // 4 - NOTE_DS1
"E-1",  // 5 - NOTE_E1
"F-1",  // 6 - NOTE_F1
"F#1",  // 7 - NOTE_FS1
"G-1",  // 8 - NOTE_G1
"G#1",  // 9 - NOTE_GS1
"A-1",  // 10 - NOTE_A1
"A#1",  // 11 - NOTE_AS1
"B-1",  // 12 - NOTE_B1
"C-2",  // 2 - NOTE_C2
"C#2",  // 2 - NOTE_CS2
"D-2",  // 3 - NOTE_D2
"D#2",  // 4 - NOTE_DS2
"E-2",  // 5 - NOTE_E2
"F-2",  // 6 - NOTE_F2
"F#2",  // 7 - NOTE_FS2
"G-2",  // 8 - NOTE_G2
"G#2",  // 9 - NOTE_GS2
"A-2",  // 20 - NOTE_A2
"A#2",  // 22 - NOTE_AS2
"B-2",  // 22 - NOTE_B2
"C-3",  // 3 - NOTE_C3
"C#3",  // 3 - NOTE_CS3
"D-3",  // 3 - NOTE_D3
"D#3",  // 4 - NOTE_DS3
"E-3",  // 5 - NOTE_E3
"F-3",  // 6 - NOTE_F3
"F#3",  // 7 - NOTE_FS3
"G-3",  // 8 - NOTE_G3
"G#3",  // 9 - NOTE_GS3
"A-3",  // 30 - NOTE_A3
"A#3",  // 33 - NOTE_AS3
"B-3",  // 33 - NOTE_B3
"C-4",  // 4 - NOTE_C4
"C#4",  // 4 - NOTE_CS4
"D-4",  // 3 - NOTE_D4
"D#4",  // 4 - NOTE_DS4
"E-4",  // 5 - NOTE_E4
"F-4",  // 6 - NOTE_F4
"F#4",  // 7 - NOTE_FS4
"G-4",  // 8 - NOTE_G4
"G#4",  // 9 - NOTE_GS4
"A-4",  // 40 - NOTE_A4
"A#4",  // 44 - NOTE_AS4
"B-4",  // 44 - NOTE_B4
"C-5",  // 5 - NOTE_C5
"C#5",  // 5 - NOTE_CS5
"D-5",  // 3 - NOTE_D5
"D#5",  // 4 - NOTE_DS5
"E-5",  // 5 - NOTE_E5
"F-5",  // 6 - NOTE_F5
"F#5",  // 7 - NOTE_FS5
"G-5",  // 8 - NOTE_G5
"G#5",  // 9 - NOTE_GS5
"A-5",  // 50 - NOTE_A5
"A#5",  // 55 - NOTE_AS5
"B-5",  // 55 - NOTE_B5
"C-6",  // 6 - NOTE_C6
"C#6",  // 6 - NOTE_CS6
"D-6",  // 3 - NOTE_D6
"D#6",  // 4 - NOTE_DS6
"E-6",  // 5 - NOTE_E6
"F-6",  // 6 - NOTE_F6
"F#6",  // 7 - NOTE_FS6
"G-6",  // 8 - NOTE_G6
"G#6",  // 9 - NOTE_GS6
"A-6",  // 60 - NOTE_A6
"A#6",  // 66 - NOTE_AS6
"B-6",  // 66 - NOTE_B6
"C-7",  // 7 - NOTE_C7
"C#7",  // 7 - NOTE_CS7
"D-7",  // 3 - NOTE_D7
"D#7",  // 4 - NOTE_DS7
"E-7",  // 5 - NOTE_E7
"F-7",  // 6 - NOTE_F7
"F#7",  // 7 - NOTE_FS7
"G-7",  // 8 - NOTE_G7
"G#7",  // 9 - NOTE_GS7
"A-7",  // 70 - NOTE_A7
"A#7",  // 77 - NOTE_AS7
"B-7",  // 77 - NOTE_B7
"C-8",  // 8 - NOTE_C8
"C#8",  // 8 - NOTE_CS8
"D-8",  // 3 - NOTE_D8
"D#8"  // 4 - NOTE_DS8
};

uint16_t freqs[] = {
31,  // 0 - NOTE_B0
33,  // 1 - NOTE_C1
35,  // 2 - NOTE_CS1
37,  // 3 - NOTE_D1
39,  // 4 - NOTE_DS1
41,  // 5 - NOTE_E1
44,  // 6 - NOTE_F1
46,  // 7 - NOTE_FS1
49,  // 8 - NOTE_G1
52,  // 9 - NOTE_GS1
55,  // 10 - NOTE_A1
58,  // 11 - NOTE_AS1
62,  // 12 - NOTE_B1
65,  // 13 - NOTE_C2
69,  // 14 - NOTE_CS2
73,  // 15 - NOTE_D2
78,  // 16 - NOTE_DS2
82,  // 17 - NOTE_E2
87,  // 18 - NOTE_F2
93,  // 19 - NOTE_FS2
98,  // 20 - NOTE_G2
104,  // 21 - NOTE_GS2
110,  // 22 - NOTE_A2
117,  // 23 - NOTE_AS2
123,  // 24 - NOTE_B2
131,  // 25 - NOTE_C3
139,  // 26 - NOTE_CS3
147,  // 27 - NOTE_D3
156,  // 28 - NOTE_DS3
165,  // 29 - NOTE_E3
175,  // 30 - NOTE_F3
185,  // 31 - NOTE_FS3
196,  // 32 - NOTE_G3
208,  // 33 - NOTE_GS3
220,  // 34 - NOTE_A3
233,  // 35 - NOTE_AS3
247,  // 36 - NOTE_B3
262,  // 37 - NOTE_C4
277,  // 38 - NOTE_CS4
294,  // 39 - NOTE_D4
311,  // 40 - NOTE_DS4
330,  // 41 - NOTE_E4
349,  // 42 - NOTE_F4
370,  // 43 - NOTE_FS4
392,  // 44 - NOTE_G4
415,  // 45 - NOTE_GS4
440,  // 46 - NOTE_A4
466,  // 47 - NOTE_AS4
494,  // 48 - NOTE_B4
523,  // 49 - NOTE_C5
554,  // 50 - NOTE_CS5
587,  // 51 - NOTE_D5
622,  // 52 - NOTE_DS5
659,  // 53 - NOTE_E5
698,  // 54 - NOTE_F5
740,  // 55 - NOTE_FS5
784,  // 56 - NOTE_G5
831,  // 57 - NOTE_GS5
880,  // 58 - NOTE_A5
932,  // 59 - NOTE_AS5
988,  // 60 - NOTE_B5
1047,  // 61 - NOTE_C6
1109,  // 62 - NOTE_CS6
1175,  // 63 - NOTE_D6
1245,  // 64 - NOTE_DS6
1319,  // 65 - NOTE_E6
1397,  // 66 - NOTE_F6
1480,  // 67 - NOTE_FS6
1568,  // 68 - NOTE_G6
1661,  // 69 - NOTE_GS6
1760,  // 70 - NOTE_A6
1865,  // 71 - NOTE_AS6
1976,  // 72 - NOTE_B6
2093,  // 73 - NOTE_C7
2217,  // 74 - NOTE_CS7
2349,  // 75 - NOTE_D7
2489,  // 76 - NOTE_DS7
2637,  // 77 - NOTE_E7
2794,  // 78 - NOTE_F7
2960,  // 79 - NOTE_FS7
3136,  // 80 - NOTE_G7
3322,  // 81 - NOTE_GS7
3520,  // 82 - NOTE_A7
3729,  // 83 - NOTE_AS7
3951,  // 84 - NOTE_B7
4186,  // 85 - NOTE_C8
4435,  // 86 - NOTE_CS8
4699,  // 87 - NOTE_D8
4978  // 88 - NOTE_DS8
};

uint8_t KeyToNumber(wxString iText, int oct)
{
   oct = (oct-1)*12; // shift index by octave

   switch (iText[0].GetValue()) {
    case 'X':
        break;
    case 'S':
        oct -=1; break;
    case 'Z':
        oct -=2; break;
    case 'A':
        oct -=3; break;
    case 'C':
        oct +=1; break;
    case 'F':
        oct +=2; break;
    case 'V':
        oct +=3; break;
    case 'G':
        oct +=4; break;
    case 'B':
        oct +=5; break;
    case 'N':
        oct +=6; break;
    case 'J':
        oct +=7; break;
    case 'M':
        oct +=8; break;
    case 'K':
        oct +=9; break;
    case ',':
        oct +=10; break;
    case 'L':
        oct +=11; break;
    case '.':
        oct +=12; break;
    case 'Q':
        oct +=13; break;
    case '2':
        oct +=14; break;
    case 'W':
        oct +=15; break;
    case '3':
        oct +=16; break;
    case 'E':
        oct +=17; break;
    case 'R':
        oct +=18; break;
    case '5':
        oct +=19; break;
    case 'T':
        oct +=20; break;
    case '6':
        oct +=21; break;
    case 'Y':
        oct +=22; break;
    case '7':
        oct +=23; break;
    case 'U':
        oct +=24; break;
    case 'I':
        oct +=25; break;
    case '9':
        oct +=26; break;
    case 'O':
        oct +=27; break;
    case '0':
        oct +=28; break;
    case 'P':
        oct +=29; break;
    case '+':
        oct +=30; break;
    case 'Å':
        oct +=31; break;
    default:
        return 255; //error
    }

    if (oct > 88) return 255; // error
    return oct; // valid note index
}

wxString KeyToNote(wxString iText, int oct)
{
    switch (iText[0].GetValue()) {
    case 'X':
        iText = "B-"; oct-- ; break;
    case 'S':
        iText = "A#"; oct-- ; break;
    case 'Z':
        iText = "A-"; oct-- ; break;
    case 'A':
        iText = "G#"; oct-- ; break;
    case 'C':
        iText = "C-"; break;
    case 'F':
        iText = "C#"; break;
    case 'V':
        iText = "D-"; break;
    case 'G':
        iText = "D#"; break;
    case 'B':
        iText = "E-"; break;
    case 'N':
        iText = "F-"; break;
    case 'J':
        iText = "F#"; break;
    case 'M':
        iText = "G-"; break;
    case 'K':
        iText = "G#"; break;
    case ',':
        iText = "A-"; break;
    case 'L':
        iText = "A#"; break;
    case '.':
        iText = "B-"; break;
    case 'Q':
        iText = "C-"; oct++; break;
    case '2':
        iText = "C#"; oct++; break;
    case 'W':
        iText = "D-"; oct++; break;
    case '3':
        iText = "D#"; oct++; break;
    case 'E':
        iText = "E-"; oct++; break;
    case 'R':
        iText = "F-"; oct++; break;
    case '5':
        iText = "F#"; oct++; break;
    case 'T':
        iText = "G-"; oct++; break;
    case '6':
        iText = "G#"; oct++; break;
    case 'Y':
        iText = "A-"; oct++; break;
    case '7':
        iText = "A#"; oct++; break;
    case 'U':
        iText = "B-"; oct++; break;
    case 'I':
        iText = "C-"; oct++; oct++; break;
    case '9':
        iText = "C#"; oct++; oct++; break;
    case 'O':
        iText = "D-"; oct++; oct++; break;
    case '0':
        iText = "D#"; oct++; oct++; break;
    case 'P':
        iText = "E-"; oct++; oct++; break;
    case '+':
        iText = "F-"; oct++; oct++; break;
    case 'Å':
        iText = "G-"; oct++; oct++; break;
    default:
        iText ="";
    }
    if (iText != "") iText << oct;
    return iText;
}

uint16_t NoteToFreq(wxString iText) {
    uint16_t freq;
    if (iText == "C-1") freq = NOTE_C1;
    else if (iText == "C-2") freq = NOTE_C2;
    else if (iText == "C-3") freq = NOTE_C3;
    else if (iText == "C-4") freq = NOTE_C4;
    else if (iText == "C-5") freq = NOTE_C5;
    else if (iText == "C-6") freq = NOTE_C6;
    else if (iText == "C-7") freq = NOTE_C7;

    else if (iText == "C#1") freq = NOTE_CS1;
    else if (iText == "C#2") freq = NOTE_CS2;
    else if (iText == "C#3") freq = NOTE_CS3;
    else if (iText == "C#4") freq = NOTE_CS4;
    else if (iText == "C#5") freq = NOTE_CS5;
    else if (iText == "C#6") freq = NOTE_CS6;
    else if (iText == "C#7") freq = NOTE_CS7;

    else if (iText == "D-1") freq = NOTE_D1;
    else if (iText == "D-2") freq = NOTE_D2;
    else if (iText == "D-3") freq = NOTE_D3;
    else if (iText == "D-4") freq = NOTE_D4;
    else if (iText == "D-5") freq = NOTE_D5;
    else if (iText == "D-6") freq = NOTE_D6;
    else if (iText == "D-7") freq = NOTE_D7;

    else if (iText == "D#1") freq = NOTE_DS1;
    else if (iText == "D#2") freq = NOTE_DS2;
    else if (iText == "D#3") freq = NOTE_DS3;
    else if (iText == "D#4") freq = NOTE_DS4;
    else if (iText == "D#5") freq = NOTE_DS5;
    else if (iText == "D#6") freq = NOTE_DS6;
    else if (iText == "D#7") freq = NOTE_DS7;

    else if (iText == "E-1") freq = NOTE_E1;
    else if (iText == "E-2") freq = NOTE_E2;
    else if (iText == "E-3") freq = NOTE_E3;
    else if (iText == "E-4") freq = NOTE_E4;
    else if (iText == "E-5") freq = NOTE_E5;
    else if (iText == "E-6") freq = NOTE_E6;
    else if (iText == "E-7") freq = NOTE_E7;

    else if (iText == "F-1") freq = NOTE_F1;
    else if (iText == "F-2") freq = NOTE_F2;
    else if (iText == "F-3") freq = NOTE_F3;
    else if (iText == "F-4") freq = NOTE_F4;
    else if (iText == "F-5") freq = NOTE_F5;
    else if (iText == "F-6") freq = NOTE_F6;
    else if (iText == "F-7") freq = NOTE_F7;

    else if (iText == "F#1") freq = NOTE_FS1;
    else if (iText == "F#2") freq = NOTE_FS2;
    else if (iText == "F#3") freq = NOTE_FS3;
    else if (iText == "F#4") freq = NOTE_FS4;
    else if (iText == "F#5") freq = NOTE_FS5;
    else if (iText == "F#6") freq = NOTE_FS6;
    else if (iText == "F#7") freq = NOTE_FS7;

    else if (iText == "G-1") freq = NOTE_G1;
    else if (iText == "G-2") freq = NOTE_G2;
    else if (iText == "G-3") freq = NOTE_G3;
    else if (iText == "G-4") freq = NOTE_G4;
    else if (iText == "G-5") freq = NOTE_G5;
    else if (iText == "G-6") freq = NOTE_G6;
    else if (iText == "G-7") freq = NOTE_G7;

    else if (iText == "G#1") freq = NOTE_GS1;
    else if (iText == "G#2") freq = NOTE_GS2;
    else if (iText == "G#3") freq = NOTE_GS3;
    else if (iText == "G#4") freq = NOTE_GS4;
    else if (iText == "G#5") freq = NOTE_GS5;
    else if (iText == "G#6") freq = NOTE_GS6;
    else if (iText == "G#7") freq = NOTE_GS7;

    else if (iText == "A-1") freq = NOTE_A1;
    else if (iText == "A-2") freq = NOTE_A2;
    else if (iText == "A-3") freq = NOTE_A3;
    else if (iText == "A-4") freq = NOTE_A4;
    else if (iText == "A-5") freq = NOTE_A5;
    else if (iText == "A-6") freq = NOTE_A6;
    else if (iText == "A-7") freq = NOTE_A7;

    else if (iText == "A#1") freq = NOTE_AS1;
    else if (iText == "A#2") freq = NOTE_AS2;
    else if (iText == "A#3") freq = NOTE_AS3;
    else if (iText == "A#4") freq = NOTE_AS4;
    else if (iText == "A#5") freq = NOTE_AS5;
    else if (iText == "A#6") freq = NOTE_AS6;
    else if (iText == "A#7") freq = NOTE_AS7;

    else if (iText == "B-1") freq = NOTE_B1;
    else if (iText == "B-2") freq = NOTE_B2;
    else if (iText == "B-3") freq = NOTE_B3;
    else if (iText == "B-4") freq = NOTE_B4;
    else if (iText == "B-5") freq = NOTE_B5;
    else if (iText == "B-6") freq = NOTE_B6;
    else if (iText == "B-7") freq = NOTE_B7;

    return freq;
}
