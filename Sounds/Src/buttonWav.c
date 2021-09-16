#include <stdint.h>

#include "audio.h"

const uint16_t buttonData[] = 
{
#ifdef HAVE_SOUND
     32766, 32770, 32767, 32770, 32764, 32774, 32760, 32777, 32761, 32772, 32766, 32769, 32767, 32770, 32763, 32773,
     32765, 32769, 32769, 32765, 32770, 32768, 32767, 32769, 32767, 32769, 32768, 32767, 32768, 32769, 32767, 32770,
     32765, 32769, 32769, 32766, 32771, 32764, 32772, 32764, 32773, 32763, 32771, 32768, 32766, 32771, 32765, 32771,
     32765, 32771, 32765, 32770, 32767, 32768, 32768, 32769, 32765, 32772, 32763, 32772, 32766, 32770, 32766, 32769,
     32766, 32771, 32766, 32769, 32768, 32766, 32771, 32766, 32769, 32767, 32769, 32766, 32772, 32765, 32770, 32766,
     32769, 32769, 32767, 32771, 32762, 32774, 32765, 32768, 32771, 32762, 32775, 32761, 32774, 32764, 32771, 32765,
     32770, 32766, 32772, 32764, 32773, 32762, 32772, 32767, 32767, 32771, 32764, 32772, 32764, 32772, 32764, 32771,
     32765, 32772, 32766, 32767, 32771, 32763, 32774, 32765, 32768, 32768, 32768, 32768, 32770, 32766, 32768, 32754,
     32741, 32762, 32776, 32776, 32771, 32794, 32792, 32764, 32746, 32764, 32760, 32768, 32805, 32813, 32772, 32725,
     32724, 32731, 32753, 32860, 33053, 33204, 33215, 33019, 32486, 31754, 31227, 31285, 32039, 33277, 34640, 35514,
     35411, 34271, 32414, 30377, 28888, 28721, 30169, 32733, 35564, 37626, 38035, 36463, 33485, 30116, 27457, 26457,
     27733, 30943, 34941, 38345, 39930, 39003, 35780, 31489, 27607, 25331, 25492, 28231, 32621, 37120, 40234, 40866,
     38691, 34406, 29626, 25907, 24368, 25614, 29347, 34300, 38751, 41259, 40941, 37801, 32922, 28103, 24835, 24111,
     26245, 30623, 35723, 39852, 41675, 40546, 36739, 31621, 26970, 24221, 24208, 27049, 31833, 36931, 40653, 41823,
     39947, 35632, 30383, 26009, 23818, 24513, 27971, 33053, 38044, 41317, 41799, 39248, 34515, 29259, 25221, 23613,
     24973, 28936, 34184, 38962, 41706, 41522, 38368, 33348, 28194, 24608, 23624, 25657, 30049, 35386, 39856, 42024,
     41135, 37404, 32139, 27158, 24039, 23745, 26397, 31208, 36539, 40626, 42156, 40552, 36312, 30917, 26220, 23675,
     24051, 27312, 32409, 37641, 41270, 42122, 39836, 35142, 29738, 25395, 23471, 24532, 28330, 33640, 38644, 41760,
     41909, 38987, 33939, 28595, 24674, 23377, 25116, 29440, 34875, 39614, 42135, 41546, 37986, 32674, 27492, 24087,
     23458, 25895, 30636, 36090, 40437, 42296, 40967, 36848, 31409, 26514, 23684, 23774, 26838, 31915, 37262, 41142,
     42287, 40225, 35623, 30148, 25619, 23408, 24228, 27892, 33204, 38354, 41706, 42104, 39351, 34374, 28945, 24857,
     23296, 24846, 29026, 34471, 39345, 42086, 41740, 38331, 33080, 27821, 24221, 23394, 25611, 30266, 35721, 40239,
     42307, 41197, 37224, 31779, 26777, 23741, 23620, 26534, 31516, 36929, 40973, 42334, 40487, 36013, 30519, 25841,
     23438, 24056, 27559, 32821, 38046, 41567, 42181, 39640, 34766, 29310, 25053, 23305, 24639, 28681, 34091, 39055,
     41970, 41844, 38652, 33480, 28158, 24396, 23333, 25377, 29882, 35363, 39981, 42243, 41363, 37576, 32187, 27087,
     23870, 23535, 26229, 31148, 36578, 40770, 42332, 40706, 36387, 30895, 26115, 23515, 23913, 27230, 32440, 37736,
     41402, 42246, 39908, 35145, 29662, 25269, 23331, 24430, 28328, 33731, 38786, 41883, 41973, 38958, 33854, 28470,
     24573, 23311, 25125, 29522, 35007, 39749, 42201, 41528, 37892, 32539, 27369, 24023, 23458, 25972, 30763, 36251,
     40553, 42341, 40914, 36733, 31253, 26386, 23619, 23775, 26924, 32042, 37401, 41228, 42292, 40157, 35512, 30015,
     25526, 23366, 24259, 27978, 33343, 38473, 41761, 42077, 39262, 34240, 28830, 24772, 23291, 24889, 29152, 34620,
     39457, 42115, 41685, 38217, 32943, 27708, 24170, 23386, 25693, 30400, 35879, 40323, 42310, 41119, 37089, 31653,
     26682, 23717, 23641, 26631, 31664, 37073, 41041, 42324, 40398, 35873, 30392, 25761, 23415, 24074, 27676, 32956,
     38186, 41620, 42166, 39538, 34612, 29183, 24966, 23281, 24680, 28810, 34254, 39200, 42041, 41831, 38529, 33331,
     28018, 24315, 23322, 25438, 30024, 35513, 40103, 42287, 41307, 37420, 32018, 26952, 23803, 23550, 26343, 31303,
     36740, 40884, 42351, 40621, 36218, 30730, 25991, 23464, 23958, 27368, 32609, 37894, 41503, 42226, 39771, 34949,
     29483, 25151, 23304, 24529, 28500, 33911, 38946, 41945, 41915, 38789, 33659, 28309, 24476, 23326, 25263, 29704,
     35185, 39865, 42211, 41420, 37708, 32365, 27239, 23961, 23531, 26120, 30960, 36399, 40646, 42298, 40783, 36543,
     31098, 26271, 23597, 23877, 27088, 32225, 37546, 41287, 42227, 40006, 35321, 29859, 25418, 23385, 24378, 28167,
     33517, 38623, 41787, 42003, 39091, 34052, 28661, 24692, 23323, 25042, 29334, 34813, 39581, 42145, 41579, 38051,
     32735, 27546, 24091, 23455, 25843, 30592, 36058, 40440, 42304, 41013, 36887, 31440, 26515, 23667, 23743, 26795,
     31889, 37246, 41149, 42307, 40250, 35669, 30156, 25623, 23395, 24214, 27867, 33191, 38360, 41694, 42110, 39346,
     34373, 28943, 24855, 23314, 24853, 29041, 34490, 39345, 42072, 41707, 38313, 33067, 27823, 24252, 23417, 25651,
     30265, 35724, 40189, 42248, 41140, 37190, 31791, 26832, 23815, 23704, 26556, 31519, 36872, 40900, 42259, 40439,
     36019, 30567, 25940, 23531, 24109, 27558, 32759, 37967, 41473, 42139, 39613, 34807, 29375, 25146, 23373, 24655,
     28648, 34026, 38995, 41927, 41844, 38670, 33529, 28217, 24453, 23371, 25356, 29835, 35297, 39924, 42218, 41369,
     37585, 32224, 27135, 23918, 23562, 26221, 31097, 36530, 40716, 42323, 40702, 36415, 30932, 26174, 23562, 23923,
     27222, 32376, 37675, 41358, 42222, 39908, 35171, 29711, 25340, 23374, 24456, 28302, 33665, 38721, 41835, 41951,
     38963, 33892, 28534, 24628, 23349, 25134, 29486, 34947, 39688, 42157, 41522, 37896, 32596, 27419, 24058, 23491,
     25968, 30745, 36202, 40524, 42309, 40897, 36729, 31279, 26401, 23649, 23805, 26950, 32048, 37397, 41223, 42259,
     40126, 35475, 30003, 25510, 23403, 24298, 28033, 33362, 38499, 41751, 42043, 39199, 34193, 28785, 24760, 23324,
     24945, 29205, 34655, 39492, 42118, 41644, 38174, 32880, 27661, 24148, 23423, 25746, 30442, 35922, 40361, 42308,
     41081, 37022, 31582, 26613, 23695, 23689, 26678, 31730, 37125, 41097, 42316, 40356, 35800, 30304, 25694, 23408,
     24133, 27735, 33038, 38253, 41668, 42147, 39473, 34526, 29072, 24907, 23286, 24750, 28885, 34348, 39273, 42077,
     41788, 38457, 33214, 27912, 24259, 23351, 25526, 30125, 35633, 40172, 42299, 41244, 37316, 31892, 26846, 23781,
     23608, 26456, 31423, 36855, 40931, 42318, 40525, 36085, 30593, 25914, 23480, 24054, 27505, 32737, 37987, 41498,
     42164, 39640, 34823, 29366, 25125, 23367, 24647, 28637, 34017, 38994, 41913, 41824, 38674, 33544, 28240, 24487,
     23402, 25364, 29807, 35254, 39876, 42172, 41345, 37630, 32283, 27203, 23980, 23580, 26194, 31016, 36442, 40647,
     42278, 40742, 36489, 31042, 26248, 23603, 23915, 27134, 32278, 37576, 41307, 42219, 39982, 35275, 29811, 25393,
     23383, 24404, 28204, 33561, 38646, 41805, 41992, 39057, 34006, 28618, 24668, 23335, 25070, 29378, 34848, 39613,
     42148, 41569, 38014, 32702, 27512, 24091, 23468, 25889, 30625, 36093, 40452, 42304, 40973, 36857, 31404, 26501,
     23666, 23772, 26831, 31916, 37265, 41154, 42279, 40221, 35634, 30143, 25608, 23419, 24237, 27902, 33208, 38363,
     41689, 42075, 39319, 34358, 28930, 24850, 23330, 24872, 29059, 34492, 39358, 42060, 41694, 38300, 33059, 27809,
     24243, 23423, 25663, 30279, 35747, 40218, 42256, 41136, 37177, 31769, 26782, 23793, 23688, 26573, 31551, 36928,
     40951, 42268, 40436, 35972, 30514, 25872, 23493, 24116, 27593, 32828, 38041, 41523, 42126, 39588, 34730, 29304,
     25072, 23363, 24677, 28704, 34103, 39054, 41954, 41812, 38625, 33460, 28158, 24417, 23380, 25393, 29889, 35356,
     39962, 42224, 41332, 37551, 32181, 27093, 23903, 23568, 26248, 31133, 36568, 40743, 42319, 40687, 36391, 30903,
     26143, 23544, 23937, 27236, 32417, 37711, 41380, 42220, 39888, 35144, 29674, 25301, 23365, 24468, 28338, 33710,
     38763, 41854, 41941, 38945, 33855, 28504, 24592, 23358, 25151, 29529, 34981, 39707, 42159, 41495, 37881, 32558,
     27405, 24037, 23505, 25987, 30766, 36220, 40524, 42299, 40886, 36725, 31271, 26397, 23643, 23809, 26952, 32049,
     37395, 41216, 42264, 40124, 35500, 30003, 25512, 23393, 24289, 28023, 33352, 38488, 41756, 42049, 39224, 34216,
     28798, 24762, 23316, 24945, 29183, 34651, 39474, 42117, 41649, 38194, 32903, 27676, 24156, 23423, 25744, 30417,
     35904, 40328, 42294, 41084, 37050, 31621, 26648, 23729, 23696, 26675, 31685, 37079, 41036, 42291, 40356, 35847,
     30362, 25754, 23456, 24141, 27714, 32971, 38180, 41603, 42116, 39501, 34589, 29152, 24983, 23322, 24749, 28831,
     34263, 39187, 42013, 41786, 38503, 33304, 27995, 24330, 23366, 25492, 30047, 35534, 40101, 42266, 41274, 37395,
     31981, 26928, 23809, 23592, 26380, 31333, 36768, 40881, 42339, 40584, 36190, 30676, 25964, 23471, 23995, 27415,
     32648, 37923, 41506, 42207, 39743, 34915, 29436, 25142, 23323, 24578, 28550, 33952, 38967, 41939, 41890, 38753,
     33614, 28271, 24473, 23353, 25302, 29753, 35213, 39880, 42191, 41404, 37664, 32326, 27207, 23960, 23556, 26164,
     30996, 36428, 40654, 42290, 40753, 36500, 31051, 26242, 23599, 23910, 27136, 32274, 37577, 41302, 42221, 39965,
     35274, 29806, 25394, 23389, 24416, 28219, 33559, 38654, 41799, 41982, 39038, 34000, 28614, 24665, 23341, 25078,
     29384, 34852, 39614, 42151, 41552, 38007, 32696, 27507, 24087, 23464, 25899, 30621, 36100, 40460, 42300, 40973,
     36847, 31410, 26490, 23669, 23767, 26840, 31903, 37275, 41153, 42281, 40213, 35636, 30146, 25610, 23416, 24244,
     27895, 33200, 38366, 41686, 42072, 39320, 34366, 28947, 24854, 23338, 24870, 29046, 34483, 39354, 42058, 41695,
     38308, 33076, 27820, 24246, 23420, 25647, 30268, 35736, 40224, 42270, 41146, 37198, 31775, 26791, 23774, 23678,
     26551, 31535, 36939, 40959, 42300, 40443, 35989, 30511, 25848, 23479, 24088, 27583, 32832, 38062, 41554, 42150,
     39592, 34734, 29274, 25061, 23327, 24677, 28706, 34128, 39089, 41984, 41827, 38613, 33445, 28128, 24395, 23369,
     25404, 29917, 35387, 40004, 42236, 41333, 37528, 32145, 27064, 23884, 23566, 26276, 31166, 36608, 40776, 42322,
     40676, 36351, 30869, 26109, 23522, 23946, 27257, 32459, 37750, 41407, 42234, 39855, 35119, 29619, 25267, 23332,
     24477, 28358, 33755, 38803, 41888, 41951, 38923, 33817, 28450, 24553, 23320, 25170, 29548, 35040, 39750, 42206,
     41493, 37860, 32517, 27347, 24002, 23479, 26007, 30806, 36271, 40578, 42327, 40883, 36687, 31226, 26350, 23602,
     23812, 26972, 32098, 37435, 41264, 42262, 40116, 35454, 29966, 25483, 23367, 24316, 28051, 33394, 38530, 41770,
     42046, 39192, 34179, 28765, 24737, 23311, 24966, 29218, 34680, 39502, 42123, 41636, 38154, 32877, 27645, 24135,
     23430, 25761, 30457, 35929, 40359, 42296, 41066, 37016, 31583, 26621, 23702, 23717, 26698, 31736, 37123, 41072,
     42298, 40331, 35803, 30315, 25716, 23431, 24170, 27746, 33035, 38226, 41635, 42113, 39454, 34539, 29093, 24945,
     23321, 24785, 28886, 34324, 39235, 42027, 41761, 38452, 33243, 27955, 24307, 23395, 25533, 30112, 35578, 40126,
     42255, 41234, 37346, 31942, 26910, 23822, 23631, 26434, 31376, 36786, 40879, 42303, 40545, 36155, 30660, 25971,
     23506, 24028, 27454, 32655, 37927, 41476, 42183, 39710, 34896, 29438, 25152, 23352, 24592, 28561, 33951, 38956,
     41922, 41882, 38733, 33617, 28266, 24484, 23363, 25307, 29756, 35219, 39879, 42206, 41394, 37674, 32308, 27207,
     23953, 23548, 26163, 31000, 36446, 40669, 42310, 40757, 36497, 31030, 26226, 23580, 23897, 27138, 32289, 37599,
     41326, 42235, 39963, 35263, 29780, 25385, 23369, 24419, 28225, 33586, 38667, 41823, 41979, 39038, 33980, 28605,
     24659, 23341, 25085, 29405, 34857, 39634, 42141, 41554, 37983, 32686, 27499, 24089, 23475, 25901, 30645, 36098,
     40467, 42291, 40958, 36836, 31395, 26497, 23670, 23782, 26846, 31923, 37274, 41158, 42268, 40208, 35617, 30142,
     25609, 23416, 24250, 27906, 33208, 38379, 41693, 42068, 39314, 34350, 28937, 24851, 23334, 24875, 29067, 34495,
     39371, 42066, 41689, 38293, 33061, 27808, 24236, 23420, 25650, 30278, 35755, 40231, 42274, 41133, 37179, 31761,
     26773, 23770, 23674, 26564, 31551, 36952, 40971, 42294, 40438, 35972, 30498, 25849, 23470, 24106, 27585, 32852,
     38066, 41560, 42142, 39580, 34718, 29272, 25048, 23341, 24677, 28725, 34135, 39099, 41980, 41814, 38596, 33430,
     28116, 24398, 23373, 25419, 29933, 35396, 40011, 42222, 41319, 37505, 32131, 27060, 23887, 23588, 26291, 31192,
     36616, 40779, 42305, 40649, 36329, 30849, 26101, 23540, 23961, 27290, 32478, 37760, 41404, 42197, 39839, 35074,
     29616, 25262, 23365, 24505, 28396, 33771, 38814, 41865, 41924, 38885, 33801, 28434, 24576, 23344, 25198, 29576,
     35042, 39756, 42166, 41486, 37820, 32513, 27344, 24024, 23504, 26031, 30824, 36277, 40569, 42302, 40867, 36667,
     31218, 26361, 23618, 23842, 26985, 32116, 37439, 41242, 42252, 40089, 35438, 29959, 25487, 23390, 24331, 28070,
     33404, 38526, 41750, 42029, 39168, 34168, 28760, 24758, 23331, 24990, 29235, 34689, 39494, 42107, 41618, 38138,
     32869, 27647, 24166, 23444, 25790, 30467, 35933, 40348, 42279, 41052, 36997, 31581, 26620, 23732, 23713, 26727,
     31728, 37122, 41058, 42280, 40324, 35788, 30319, 25723, 23447, 24177, 27755, 33031, 38218, 41622, 42104, 39452,
     34531, 29102, 24953, 23333, 24783, 28896, 34312, 39232, 42025, 41756, 38450, 33243, 27959, 24313, 23396, 25538,
     30107, 35580, 40119, 42256, 41233, 37337, 31947, 26905, 23827, 23633, 26430, 31381, 36787, 40877, 42306, 40538,
     36142, 30666, 25962, 23512, 24034, 27450, 32673, 37914, 41491, 42165, 39709, 34893, 29433, 25159, 23351, 24596,
     28562, 33955, 38958, 41928, 41871, 38741, 33611, 28269, 24482, 23360, 25311, 29751, 35234, 39875, 42208, 41390,
     37664, 32305, 27201, 23949, 23553, 26160, 31014, 36443, 40678, 42302, 40749, 36503, 31018, 26233, 23582, 23899,
     27142, 32294, 37599, 41327, 42224, 39969, 35250, 29784, 25368, 23379, 24413, 28233, 33594, 38675, 41818, 41981,
     39029, 33977, 28593, 24656, 23336, 25084, 29406, 34868, 39635, 42142, 41559, 37978, 32683, 27487, 24085, 23467,
     25902, 30652, 36112, 40469, 42300, 40954, 36837, 31381, 26493, 23664, 23775, 26856, 31931, 37290, 41162, 42274,
     40208, 35615, 30129, 25605, 23403, 24245, 27913, 33222, 38384, 41695, 42078, 39309, 34342, 28925, 24843, 23326,
     24881, 29072, 34516, 39370, 42070, 41690, 38287, 33051, 27794, 24233, 23407, 25666, 30288, 35769, 40236, 42283,
     41145, 37176, 31756, 26770, 23754, 23669, 26565, 31558, 36960, 40974, 42307, 40442, 35979, 30493, 25844, 23459,
     24090, 27598, 32851, 38073, 41561, 42151, 39587, 34714, 29278, 25031, 23330, 24673, 28732, 34151, 39101, 41998,
     41830, 38605, 33426, 28096, 24368, 23350, 25418, 29943, 35420, 40023, 42250, 41330, 37498, 32123, 27032, 23869,
     23577, 26304, 31202, 36632, 40779, 42313, 40655, 36322, 30848, 26086, 23529, 23960, 27302, 32495, 37765, 41414,
     42203, 39843, 35070, 29601, 25250, 23352, 24511, 28414, 33787, 38817, 41868, 41930, 38883, 33797, 28428, 24561,
     23346, 25199, 29591, 35043, 39754, 42166, 41492, 37829, 32501, 27341, 24003, 23507, 26033, 30841, 36282, 40569,
     42311, 40866, 36667, 31204, 26336, 23618, 23829, 27013, 32126, 37455, 41248, 42265, 40094, 35435, 29941, 25471,
     23377, 24329, 28088, 33424, 38537, 41759, 42035, 39167, 34149, 28743, 24743, 23332, 25007, 29265, 34711, 39491,
     42103, 41601, 38126, 32841, 27637, 24163, 23464, 25812, 30508, 35939, 40352, 42264, 41046, 36977, 31559, 26615,
     23721, 23733, 26738, 31762, 37122, 41060, 42284, 40322, 35789, 30301, 25722, 23436, 24175, 27763, 33042, 38211,
     41627, 42110, 39462, 34525, 29106, 24940, 23328, 24783, 28907, 34330, 39231, 42029, 41764, 38437, 33225, 27934,
     24297, 23384, 25559, 30142, 35608, 40136, 42262, 41229, 37316, 31918, 26885, 23813, 23624, 26457, 31400, 36803,
     40881, 42309, 40533, 36132, 30644, 25963, 23495, 24043, 27479, 32691, 37926, 41478, 42165, 39683, 34871, 29429,
     25159, 23373, 24621, 28606, 33967, 38949, 41909, 41845, 38720, 33591, 28281, 24494, 23377, 25330, 29773, 35220,
     39874, 42200, 41399, 37657, 32317, 27195, 23951, 23543, 26168, 31027, 36445, 40688, 42310, 40757, 36477, 31016,
     26209, 23575, 23897, 27165, 32314, 37622, 41333, 42243, 39944, 35233, 29756, 25353, 23369, 24431, 28264, 33621,
     38686, 41827, 41969, 39014, 33950, 28587, 24646, 23352, 25105, 29442, 34875, 39631, 42129, 41536, 37956, 32662,
     27498, 24096, 23504, 25944, 30676, 36111, 40450, 42270, 40929, 36803, 31371, 26490, 23673, 23808, 26888, 31965,
     37304, 41153, 42269, 40177, 35591, 30107, 25589, 23411, 24264, 27951, 33252, 38390, 41691, 42056, 39292, 34320,
     28922, 24840, 23340, 24899, 29098, 34529, 39363, 42067, 41675, 38273, 33033, 27775, 24219, 23413, 25682, 30341,
     35799, 40257, 42275, 41118, 37132, 31722, 26745, 23763, 23690, 26605, 31611, 36975, 40981, 42292, 40421, 35948,
     30469, 25832, 23454, 24101, 27622, 32877, 38085, 41557, 42145, 39580, 34700, 29270, 25043, 23323, 24683, 28730,
     34156, 39087, 41989, 41833, 38606, 33432, 28118, 24384, 23353, 25411, 29933, 35395, 39994, 42241, 41335, 37529,
     32143, 27060, 23874, 23552, 26285, 31187, 36611, 40770, 42325, 40669, 36344, 30863, 26111, 23532, 23946, 27292,
     32466, 37744, 41393, 42223, 39867, 35099, 29631, 25250, 23336, 24470, 28396, 33764, 38817, 41878, 41964, 38908,
     33817, 28429, 24550, 23317, 25174, 29588, 35038, 39754, 42189, 41500, 37844, 32518, 27346, 24016, 23485, 26025,
     30812, 36248, 40549, 42299, 40890, 36702, 31247, 26375, 23609, 23816, 26983, 32091, 37429, 41225, 42266, 40104,
     35459, 29979, 25496, 23398, 24324, 28080, 33389, 38510, 41735, 42025, 39169, 34169, 28763, 24763, 23341, 25008,
     29253, 34689, 39484, 42080, 41604, 38124, 32855, 27664, 24167, 23482, 25800, 30490, 35930, 40334, 42271, 41028,
     36991, 31549, 26631, 23735, 23756, 26747, 31748, 37114, 41035, 42277, 40318, 35804, 30313, 25737, 23466, 24188,
     27764, 33025, 38197, 41612, 42106, 39460, 34527, 29089, 24942, 23347, 24802, 28918, 34322, 39221, 42007, 41766,
     38454, 33242, 27941, 24306, 23394, 25532, 30108, 35567, 40113, 42272, 41277, 37380, 31947, 26876, 23787, 23603,
     26436, 31399, 36806, 40869, 42302, 40540, 36142, 30662, 25967, 23521, 24050, 27468, 32670, 37900, 41447, 42169,
     39729, 34916, 29454, 25150, 23335, 24584, 28558, 33964, 38937, 41913, 41868, 38765, 33638, 28299, 24490, 23356,
     25287, 29749, 35216, 39871, 42200, 41415, 37681, 32332, 27198, 23942, 23533, 26159, 31027, 36464, 40683, 42304,
     40760, 36494, 31032, 26221, 23572, 23881, 27147, 32303, 37620, 41327, 42233, 39956, 35269, 29781, 25385, 23363,
     24412, 28236, 33609, 38688, 41829, 41978, 39026, 33963, 28590, 24634, 23339, 25087, 29432, 34887, 39635, 42124,
     41533, 37969, 32708, 27525, 24113, 23486, 25894, 30630, 36086, 40436, 42287, 40953, 36865, 31443, 26526, 23697,
     23777, 26841, 31904, 37262, 41119, 42244, 40177, 35619, 30163, 25629, 23458, 24282, 27950, 33233, 38382, 41646,
     42012, 39253, 34336, 28953, 24885, 23373, 24908, 29074, 34507, 39354, 42045, 41664, 38286, 33070, 27811, 24239,
     23406, 25655, 30295, 35775, 40266, 42267, 41130, 37169, 31758, 26768, 23758, 23662, 26573, 31575, 36999, 41000,
     42304, 40409, 35963, 30461, 25835, 23439, 24097, 27604, 32890, 38129, 41591, 42151, 39554, 34683, 29232, 25012,
     23312, 24689, 28749, 34209, 39152, 42016, 41788, 38549, 33366, 28075, 24375, 23391, 25455, 29988, 35448, 40042,
     42208, 41270, 37444, 32103, 27053, 23924, 23629, 26336, 31192, 36618, 40751, 42274, 40625, 36319, 30871, 26141,
     23573, 24000, 27289, 32455, 37725, 41363, 42175, 39836, 35118, 29670, 25313, 23380, 24481, 28336, 33699, 38779,
     41864, 41965, 38939, 33855, 28462, 24560, 23336, 25189, 29578, 35054, 39758, 42148, 41430, 37786, 32482, 27344,
     24038, 23545, 26084, 30862, 36310, 40578, 42267, 40808, 36613, 31188, 26342, 23644, 23882, 27057, 32158, 37494,
     41249, 42214, 40018, 35382, 29906, 25446, 23374, 24350, 28114, 33484, 38622, 41821, 42025, 39121, 34093, 28675,
     24682, 23298, 25002, 29278, 34769, 39596, 42160, 41614, 38105, 32811, 27596, 24115, 23430, 25795, 30477, 35980,
     40390, 42301, 41024, 36990, 31553, 26605, 23707, 23732, 26726, 31761, 37187, 41110, 42300, 40279, 35735, 30241,
     25662, 23427, 24205, 27810, 33101, 38307, 41663, 42083, 39388, 34469, 29049, 24918, 23348, 24821, 28920, 34360,
     39265, 42031, 41720, 38412, 33213, 27939, 24301, 23419, 25549, 30126, 35601, 40172, 42271, 41223, 37319, 31899,
     26856, 23780, 23634, 26452, 31414, 36847, 40933, 42303, 40505, 36097, 30609, 25931, 23510, 24092, 27503, 32702,
     37936, 41461, 42122, 39658, 34900, 29446, 25189, 23388, 24640, 28555, 33928, 38907, 41881, 41820, 38753, 33659,
     28332, 24514, 23394, 25311, 29717, 35169, 39838, 42168, 41394, 37723, 32401, 27243, 23944, 23516, 26113, 30963,
     36447, 40697, 42317, 40753, 36503, 31038, 26201, 23563, 23907, 27163, 32312, 37648, 41353, 42218, 39940, 35242,
     29780, 25328, 23362, 24413, 28236, 33615, 38730, 41865, 41976, 38997, 33945, 28550, 24621, 23347, 25128, 29438,
     34874, 39650, 42120, 41490, 37934, 32661, 27504, 24138, 23587, 25997, 30652, 36032, 40382, 42213, 40935, 36868,
     31447, 26476, 23649, 23799, 26912, 31991, 37320, 41091, 41998, 39736, 35098, 29797, 25761, 24328, 25828, 29625,
     34299, 38199, 40026, 39251, 36312, 32290, 28751, 26865, 27146, 29258, 32336, 35283, 37143, 37421, 36196, 33963,
     31528, 29743, 29137, 29746, 31218, 32982, 34476, 35249, 35232, 34476, 33328, 32103, 31232, 30909, 31170, 31839,
     32725, 33506, 34031, 34157, 33918, 33339, 32622, 31984, 31611, 31603, 31921, 32484, 33091, 33575, 33820, 33758,
     33393, 32831, 32273, 31875, 31780, 31997, 32473, 33008, 33456, 33655, 33567, 33209, 32722, 32285, 32033, 32035,
     32271, 32636, 33019, 33300, 33419, 33343, 33102, 32750, 32442, 32218, 32198, 32344, 32619, 32928, 33163, 33269,
     33190, 32980, 32692, 32471, 32363, 32417, 32571, 32784, 32972, 33103, 33130, 33048, 32877, 32654, 32490, 32404,
     32454, 32589, 32763, 32944, 33053, 33076, 33006, 32846, 32656, 32528, 32490, 32557, 32692, 32831, 32957, 32995,
     32979, 32881, 32765, 32630, 32578, 32583, 32660, 32747, 32848, 32895, 32918, 32874, 32824, 32743, 32671, 32649,
     32664, 32723,
#endif  // HAVE_SOUND
};

//-----------------------------------------------------------------------
Audio buttonSound =
{
    44100, 1,
    sizeof(buttonData),
    buttonData
};
