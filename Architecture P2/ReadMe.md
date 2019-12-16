## ΑΡΧΙΤΕΚΤΟΝΙΚΗ 2η ΕΡΓΑΣΙΑ  
#### ΤΣΟΥΡΑΚΑΣ ΔΗΜΗΤΡΗΣ 9042  
#### ΑΘΑΝΑΣΙΑΔΗΣ ΧΡΗΣΤΟΣ 9092  

Βήμα 1ο  
1. Στις προσομοιώσεις που κάνουμε στον gem5 χρησιμοποιούμε το MinorCPU μοντέλο cpu. Ο συγκεκριμένος επεξεργαστής έχει cache line με μέγεθος ίσο με 64 B. Η cache του είναι τύπου set-associative, με την L1 cache (data και instruction) να είναι 2-way set-associative, δηλαδή είναι χωρισμένη σε σύνολα κάθε ένα από τα οποία περιέχει 2 blocks, και με την L2 cache να είναι 8-way set-associative, δηλαδή είναι χωρισμένη σε σύνολα κάθε ένα από τα οποία περιέχει 8 blocks. Όσων αφορά τα μεγέθη των caches, η L1 cache που χωρίζεται στις L1 data cache και L1 instruction cache, έχει μεγέθη 65536 B και 32768 B αντίστοιχα. Η L2 cache έχει μέγεθος 2097152 B.

2. Στον gem5 εκτελέστηκαν τα παρακάτω benchmarks και τα αποτελέσματα είναι ως εξής :  
	specbzip  
 (i) Χρόνος εκτέλεσης = 0.083982 (sim_seconds)  
 (ii) CPI = 1.679650 (system.cpu.cpi)  
 (iii) miss rates: L1 Data cache = 0.014798 (system.cpu.dcache.overall_miss_rate::total)  
		   L1 Instruction cache = 0.000077 (system.cpu.icache.overall_miss_rate::total)  
		   L2 cache = 0.282163 (system.l2.overall_miss_rate::total)  
	specmcf  
 (i) Χρόνος εκτέλεσης = 0.064955  
 (ii) CPI = 1.299095  
 (iii) miss rates: L1 Data cache = 0.002108  
		   L1 Instruction cache = 0.023612  
		   L2 cache = 0.055046  
	spechmmer  
 (i) Χρόνος εκτέλεσης = 0.059396  
 (ii) CPI = 1.187917  
 (iii) miss rates: L1 Data cache = 0.001637  
		   L1 Instruction cache = 0.000221  
		   L2 cache = 0.077760  
	specsjeng  
 (i) Χρόνος εκτέλεσης = 0.513528  
 (ii) CPI = 10.270554  
 (iii) miss rates: L1 Data cache = 0.121831  
		   L1 Instruction cache = 0.000020  
		   L2 cache = 0.999972  
	speclibm  
 (i) Χρόνος εκτέλεσης = 0.174671  
 (ii) CPI = 3.493415   
 (iii) miss rates: L1 Data cache = 0.060972  
		   L1 Instruction cache = 0.000094  
		   L2 cache = 0.9999440  
Παρατηρούμε ότι όσο μεγαλύτερο είναι το miss rate στις caches τόσο περισσότερος χρόνος απαιτείται για να εκτελεστεί το κάθε benchmark. Αυτό συμβαίνει διότι έχουμε περισσότερες προσβάσεις στην κύρια μνήμη η οποία είναι αργή και καθυστερεί την εκτέλεση. Επίσης όσο μικρότερο  είναι το CPI τόσο γρηγορότερα εκτελείται το benchmark. Για παράδειγμα, το specsjeng benchmark που έχει σχετικά μεγάλο CPI αλλά και σχεδόν 1 miss rate στην L2 cache, αργεί να εκτελεστεί καθώς ο χρόνος εκτέλεσης είναι περίπου δεκαπλάσιος από τον χρόνο που κάνουν τα υπόλοιπα benchmark. Με κατάλληλες αλλαγές στα χαρακτηριστικά των caches αλλά και της συχνότητας της cpu, ο χρόνος αυτος μπορεί να μειωθεί αρκετά.  

3. Τρέχοντας τα παραπάνω benchmarks με την παράμετρο --cpu-clock=1GHz παίρνουμε τις εξής πληροφορίες για το ρολόι :  
	specbzip  
(χωρίς την παράμετρο --cpu-clock=1GHz)  
system.clk_domain.clock = 1000  
cpu_cluster.clk_domain.clock = 500  
(με την παράμετρο --cpu-clock=1GHz)  
system.clk_domain.clock = 1000  
cpu_cluster.clk_domain.clock = 1000  

	specmcf  
(χωρίς την παράμετρο --cpu-clock=1GHz)  
system.clk_domain.clock = 1000  
cpu_cluster.clk_domain.clock = 500  
(με την παράμετρο --cpu-clock=1GHz)  
system.clk_domain.clock = 1000  
cpu_cluster.clk_domain.clock = 1000  

Παρατηρούμε αρχικά ότι χωρίς την παράμετρο --cpu-clock=1GHz ο cpu χρονίζεται στα 2GHz by default από τις ρυθμίσεις, καθώς βλέπουμε στα στατιστικά ότι η περίοδος του ρολογιού της cpu είναι 500nseconds. Χρησιμοποιώντας την παράμετρο, η περίοδος ρολογιού της cpu γίνεται 1000nseconds που σημαίνει ότι χρονίζεται στο 1GHz. Επίσης παρατηρούμε ότι system.clk_domain.clock παραμένει σταθερό στα 1000nseconds παρ'όλες τις αλλαγές που κάνουμε ή δεν κάνουμε. Αυτό συμβαίνει διότι το ρολόι αυτό δεν σχετίζεται με το ρολόι της cpu μας, αλλά αντιπροσωπεύει την συχνότητα της προσομοίωσης.  

Χρόνοι εκτέλεσης των benchmarks με --cpu-clock=1GHz :  
	  sim_seconds     CPI  
specbzip   0.161025     1.610247  
specmcf    0.127942     1.279422  
spechmmer  0.118530     1.185304  
specsjeng  0.704056     7.040561  
speclibm   0.262327     2.623265  

Παρατηρούμε ότι με διπλασιασμό της συχνότητας της cpu έχουμε μείωση του χρόνου εκτέλεσης σχεδόν στον μισό σε κάθε benchmark. Γενικά δεν υπάρχει τέλειο scaling καθώς οι δυνατότητες του επεξεργαστή μας δεν αξιοποιούνται πλήρως, καθώς έχουμε καθυστερήσεις από την κρυφή και την κύρια μνήμη. Υποθέτοντας ότι αυτές οι καθυστερήσεις δεν υπάρχουν, με διπλασιασμό της συχνότητας της cpu, περιμένουμε μείωση του χρόνου εκτέλεσης ακριβώς στον μισό.  
![Benchmarks](/Architecture%20P2/src/Documents/Benchmarks.png "Benchmarks")


Βήμα 2ο  
1. Δοκιμές για το 1ο benchmark :  
Το συγκεκριμένο benchmark χρησιμοποιείται για την συμπίεση και την αποσυμπίεση αρχείων. Από την εκτέλεση του benchmark με τις default ρυθμίσεις στο 1ο βήμα παρατηρούμε ότι το CPI είναι 1.610247. Καθώς εμείς προσπαθούμε να πετύχουμε CPI ίσο με το 1, μπορούμε να κάνουμε αλλαγές στις ρυθμίσεις της cache ώστε να το βελτιώσουμε. Παρατηρώντας τα miss rate που έχουμε σε κάθε επίπεδο της cache βλέπουμε ότι οι L1 Instruction cache και L2 cache έχουν αρκετά misses για τα οποία η cache επιδέχεται βελτίωση. Η L1 Data cache από την άλλη φαίνεται να έχει μηδαμινά misses. Αυτό συμβαίνει, ενδεχομένως, διότι το συγκεκριμένο benchmark δεν συμπεριλαμβάνει πολλές εντολές για την εκτέλεσή του. Επομένως κάθε αλλαγή στην L1 Instruction cache θα επιφέρει ελάχιστες (εάν όχι και καθόλου) βελτιώσεις. Για την μείωση των misses μπορούμε είτε να αυξήσουμε το μέγεθος (με κόστος να έχουμε λίγο πιο αργή μνήμη), είτε να αυξήσουμε το associativity του κάθε επιπέδου cache. Μεγαλώνοντας λοιπόν τα μεγέθη και το association της L1 και της L2 παρατηρούμε βελτίωση στα miss rates και μείωση του CPI. Επίσης η αύξηση του μεγέθους της cacheline βελτιώνει και αυτή το CPI μας. Παρακάτω φαίνονται μερικές δοκιμές και τα αποτελέσματά τους. 

Αύξηση assoc για L1 (βελτίωση στα miss rate της L1)  
--l1d_size=64kB --l1i_size=64kB --l2_size=512kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=8 --cacheline_size=64  
specbzip2_0             1.747352             0.013324             0.000070             0.436026

Αύξηση της cache line (βελτίωση στα miss rate της L1 και της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=512kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=8 --cacheline_size=128  
specbzip2_1             1.731613             0.012827             0.000053             0.318973  

Αύξηση του μεγέθους της L2 (βελτίωση στο miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=1024kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=8 --cacheline_size=64  
specbzip2_2             1.694702             0.013332             0.000070             0.356782

Αύξηση της cache line και αύξηση του μεγέθους της L2 (βελτίωση στo miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=1024kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=8 --cacheline_size=128  
specbzip2_3             1.674064             0.012828             0.000053             0.229720

Μείωση assoc για L1 (αύξηση στα miss rate της L1)  
--l1d_size=64kB --l1i_size=64kB --l2_size=512kB --l1i_assoc=1 --l1d_assoc=1 --l2_assoc=8 --cacheline_size=128  
specbzip2_4             1.785882             0.017855             0.000063             0.226463

Μείωση assoc για L2 (αύξηση στο miss rate της L2)  
-l1d_size=64kB --l1i_size=64kB --l2_size=512kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=4 --cacheline_size=128  
specbzip2_5             1.733933             0.012826             0.000053             0.324431

Αύξηση του μεγέθους της L2 (βελτίωση στο miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=2048kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=4 --cacheline_size=128  
specbzip2_6             1.649439             0.012825             0.000053             0.196262

Αύξηση του μεγέθους της L2 (βελτίωση στο miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=4096kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=4 --cacheline_size=128  
specbzip2_7             1.632153             0.012808             0.000053             0.174218

Αύξηση του μεγέθους της L1 και μείωση assoc για L2(βελτίωση στα miss rate της L1 και αύξηση στα miss rate της L2)  
--l1d_size=128kB --l1i_size=128kB --l2_size=4096kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=2 --cacheline_size=128  
specbzip2_8             1.608796             0.009823             0.000052             0.231588

Μείωση του assoc της L1 και της cache line (αύξηση στα miss rate της L1 και της L2)  
--l1d_size=128kB --l1i_size=128kB --l2_size=4096kB --l1i_assoc=2 --l1d_assoc=2 --l2_assoc=4 --cacheline_size=64  
specbzip2_9             1.568549             0.011618             0.000070             0.324134

Αύξηση της cache line (βελτίωση στα miss rate της L1 και της L2)  
--l1d_size=128kB --l1i_size=128kB --l2_size=4096kB --l1i_assoc=2 --l1d_assoc=2 --l2_assoc=4 --cacheline_size=256  
specbzip2_10             1.561447             0.011133             0.000040             0.133308


Δοκιμές για το 2ο benchmark :  
Το συγκεκριμένο benchmark χρησιμοποιείται για τον προγραμματισμό οχημάτων με ένα αμαξοστάσιο στις δημόσιες μαζικές μεταφορές. Από την εκτέλεση του benchmark με τις default ρυθμίσεις στο 1ο βήμα παρατηρούμε ότι το CPI είναι 1.279422. Παρατηρούμε οτι βρισκόμαστε ήδη κοντά στο επιθυμητό CPI καθώς όλα τα miss rate στα επίπεδα της L1 cache είναι χαμηλά. Παρόλα αυτά, έχουμε ανεβασμένο miss rate στην L2 cache, οπότε με αλλαγές στις ρυθμίσεις της ίσως έχουμε ακόμη καλύτερα αποτελέσματα. Παρακάτω φαίνονται μερικές δοκιμές και τα αποτελέσματά τους.

Αύξηση assoc για L1 (βελτίωση στα miss rate της L1)  
--l1d_size=64kB --l1i_size=64kB --l2_size=512kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=8 --cacheline_size=64  
specmcf_0		1.142751	0.001970	0.000018	0.881828

Αύξηση της cache line (βελτίωση στα miss rate της L1 και της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=512kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=8 --cacheline_size=128  
specmcf_1		1.112112	0.001246	0.000013	0.597267

Αύξηση του μεγέθους της L2 (βελτίωση στο miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=1024kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=8 --cacheline_size=64  
specmcf_2		1.140733	0.001970	0.000018	0.819520

Αύξηση της cache line και αύξηση του μεγέθους της L2 (βελτίωση στo miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=1024kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=8 --cacheline_size=128  
specmcf_3		1.114410	0.001246	0.000013	0.667934

Μείωση assoc για L1 (αύξηση στα miss rate της L1)  
--l1d_size=64kB --l1i_size=64kB --l2_size=512kB --l1i_assoc=1 --l1d_assoc=1 --l2_assoc=8 --cacheline_size=128  
specmcf_4		1.124604	0.002312	0.000034	0.406700

Μείωση assoc για L2 (αύξηση στο miss rate της L2)  
-l1d_size=64kB --l1i_size=64kB --l2_size=512kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=4 --cacheline_size=128  
specmcf_5		1.117873	0.001246	0.000013	0.776415

Αύξηση του μεγέθους της L2 (βελτίωση στο miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=2048kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=4 --cacheline_size=128  
specmcf_6		1.112112	0.001246	0.000013	0.597267

Αύξηση του μεγέθους της L2 (βελτίωση στο miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=4096kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=4 --cacheline_size=128  
specmcf_7		1.111918	0.001246	0.000013	0.590910

Αύξηση του μεγέθους της L1 και μείωση assoc για L2(βελτίωση στα miss rate της L1 και αύξηση στα miss rate της L2)  
--l1d_size=128kB --l1i_size=128kB --l2_size=4096kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=2 --cacheline_size=128  
specmcf_8		1.111239	0.001120	0.000013	0.653408

Αύξηση της cache line (βελτίωση στα miss rate της L1 και της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=2048kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=4 --cacheline_size=256  
specmcf_9		1.100838	0.000921	0.000009	0.382600

Αύξηση του μεγέθους της L2 (βελτίωση στο miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=4096kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=4 --cacheline_size=256  
specmcf_10		1.100750	0.000921	0.000009	0.379348

Μείωση assoc για L1 (αύξηση στο miss rate της L1)  
--l1d_size=64kB --l1i_size=64kB --l2_size=2048kB --l1i_assoc=2 --l1d_assoc=2 --l2_assoc=4 --cacheline_size=256  
specmcf_11		1.102712	0.001172	0.000027	0.292813

Αύξηση του μεγέθους της L2 (βελτίωση στο miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=4096kB --l1i_assoc=2 --l1d_assoc=2 --l2_assoc=4 --cacheline_size=256  
specmcf_12		1.102621	0.001172	0.000027	0.290181


Δοκιμές για το 3ο benchmark :  
Το συγκεκριμένο benchmark χρησιμοποιείται για την αναζήτηση βάσης δεδομένων αλληλουχίας γονιδίων. Όπως και στο προηγούμενο benchmark, παρατηρούμε πως το CPI είναι αρκετα κοντά στο 1 (1.185304) όταν εκτελούμε το benchmark με default ρυθμίσεις. Πάλι όμως μπορούμε να βελτιώσουμε το CPI (έστω και λίγο) με αλλαγές στην cache. Παρακάτω φαίνονται μερικές δοκιμές και τα αποτελέσματά τους. 

Αύξηση assoc για L1 (βελτίωση στα miss rate της L1)  
--l1d_size=64kB --l1i_size=64kB --l2_size=512kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=8 --cacheline_size=64  
spechmmer_0		1.189092	0.002331	0.000084 	0.097571

Αύξηση της cache line (βελτίωση στα miss rate της L1)  
--l1d_size=64kB --l1i_size=64kB --l2_size=512kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=8 --cacheline_size=128  
spechmmer_1		1.181915	0.001184	0.000064	0.100425 

Αύξηση του μεγέθους της L2 (βελτίωση στο miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=1024kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=8 --cacheline_size=64  
spechmmer_2		1.189082	0.002331	0.000084	0.097453

Αύξηση της cache line και αύξηση του μεγέθους της L2 (βελτίωση στo miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=1024kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=8 --cacheline_size=128  
spechmmer_3		1.181902	0.001184	0.000064	0.100153

Μείωση assoc για L1 (αύξηση στα miss rate της L1)  
--l1d_size=64kB --l1i_size=64kB --l2_size=512kB --l1i_assoc=1 --l1d_assoc=1 --l2_assoc=8 --cacheline_size=128  
spechmmer_4		1.207712	0.003162	0.000369	0.036213

Μείωση assoc για L2 (αύξηση στο miss rate της L2)  
-l1d_size=64kB --l1i_size=64kB --l2_size=512kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=4 --cacheline_size=128  
spechmmer_5		1.181964	0.001184	0.000064	0.101263

Αύξηση του μεγέθους της L2 (βελτίωση στο miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=2048kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=4 --cacheline_size=128  
spechmmer_6		1.181902	0.001184	0.000064	0.100153

Αύξηση του μεγέθους της L2 (ίδιο miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=4096kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=4 --cacheline_size=128  
spechmmer_7		1.181902	0.001184	0.000064	0.100153

Αύξηση του μεγέθους της L1 και μείωση assoc για L2(βελτίωση στα miss rate της L1 και αύξηση στα miss rate της L2)  
--l1d_size=128kB --l1i_size=128kB --l2_size=4096kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=2 --cacheline_size=128  
spechmmer_8		1.181615	0.001132	0.000057	0.104814

Αύξηση της cache line (βελτίωση στα miss rate της L1 και της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=1024kB --l1i_assoc=2 --l1d_assoc=2 --l2_assoc=8 --cacheline_size=256  
spechmmer_9		1.177972 	0.000544	0.000074	0.070031

Αύξηση του μεγέθους της L1 (αύξηση στα miss rate της L1)  
--l1d_size=128kB --l1i_size=128kB --l2_size=1024kB --l1i_assoc=2 --l1d_assoc=2 --l2_assoc=8 --cacheline_size=256  
spechmmer_10	1.178368	0.000579	0.000040	0.107986

Αύξηση της cache line (βελτίωση στα miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=1024kB --l1i_assoc=2 --l1d_assoc=2 --l2_assoc=8 --cacheline_size=512  
spechmmer_11	1.179780	0.000578	0.000078	0.037121


Δοκιμές για το 4ο benchmark :  
Το συγκεκριμένο benchmark είναι ένα πρόγραμμα που παίζει σκάκι και διάφορες παραλλαγές σκακιού, υπολογίζει δηλαδή την βέλτιστη κίνηση σε κάθε γύρο του παιχνιδιού. To CPI από την εκτέλεση του benchmark με τις default ρυθμίσεις είναι πολύ μεγάλο (7.040561). Επιπλέον παρατηρούμε ότι έχουμε μεγάλο αριθμό miss rate  στις L1 Data και L2. Αλλάζοντας παραμέτρους της cache μπορούμε να βελτιώσουμε τα στατιστικά αυτά. Με αύξηση της cache line παρατηρούμε ότι τα misses αλλά και το CPI μειώνονται αισθητά καθώς το συγκεκριμένο benchmark φαίνεται πως εκμεταλεύεται καλά την τοπικότητα των δεδομένων. Παρακάτω φαίνονται μερικές δοκιμές και τα αποτελέσματά τους.

Αύξηση assoc για L1 (βελτίωση στα miss rate της L1)  
--l1d_size=64kB --l1i_size=64kB --l2_size=512kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=8 --cacheline_size=64  
specjeng_0	7.040538	0.121831	0.000019 	0.999985

Αύξηση της cache line (βελτίωση στα miss rate της L1)  
--l1d_size=64kB --l1i_size=64kB --l2_size=512kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=8 --cacheline_size=128  
specjeng_1	4.975118	0.060918	0.000013	0.999973 

Αύξηση του μεγέθους της L2 (ίδιο miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=1024kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=8 --cacheline_size=64  
specjeng_2	7.041083	0.121831	0.000019	0.999985

Αύξηση της cache line και αύξηση του μεγέθους της L2 (βελτίωση στo miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=1024kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=8 --cacheline_size=128  
specjeng_3	4.975723	0.060918	0.000013	0.999973

Μείωση assoc για L1 (αύξηση στα miss rate της L1)  
--l1d_size=64kB --l1i_size=64kB --l2_size=512kB --l1i_assoc=1 --l1d_assoc=1 --l2_assoc=8 --cacheline_size=128  
specjeng_4	5.013971	0.062028	0.000014	0.964875

Μείωση assoc για L2 (ίδιο miss rate της L2)  
-l1d_size=64kB --l1i_size=64kB --l2_size=512kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=4 --cacheline_size=128  
specjeng_5	4.976473	0.060918	0.000013	0.999973

Αύξηση του μεγέθους της L2 (ίδιο miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=2048kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=4 --cacheline_size=128  
specjeng_6	4.974751	0.060918	0.000013	0.999973

Αύξηση του μεγέθους της L1 και μείωση assoc για L2(ίδια miss rate της L1 και αύξηση στα miss rate της L2)  
--l1d_size=128kB --l1i_size=128kB --l2_size=4096kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=2 --cacheline_size=128  
specjeng_7	4.972571	0.060918 	0.000013 	0.999978

Μείωση assoc για L1 και cache line (αύξηση στα miss rate της L1)  
--l1d_size=64kB --l1i_size=32kB --l2_size=256kB --l1i_assoc=2 --l1d_assoc=2 --l2_assoc=8 --cacheline_size=64  
specjeng_8	7.040931	0.121831 	0.000020 	0.999972

Αύξηση της cache line (βελτίωση στα miss rate της L1 και της L2)  
--l1d_size=64kB --l1i_size=32kB --l2_size=256kB --l1i_assoc=2 --l1d_assoc=2 --l2_assoc=8 --cacheline_size=128  
specjeng_9	4.975871	0.060922 	0.000015	0.999826

Αύξηση της cache line (βελτίωση στα miss rate της L1 και της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=1024kB --l1i_assoc=2 --l1d_assoc=2 --l2_assoc=8 --cacheline_size=256  
specjeng_10	3.715957	0.030472 	0.000009 	0.999218

Αύξηση της cache line (βελτίωση στα miss rate της L1 και της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=1024kB --l1i_assoc=2 --l1d_assoc=2 --l2_assoc=8 --cacheline_size=512  
specjeng_11	3.071704	0.015279 	0.000008  	0.993690

Αύξηση της cache line (βελτίωση στα miss rate της L1 και της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=1024kB --l1i_assoc=2 --l1d_assoc=2 --l2_assoc=8 --cacheline_size=1024  
specjeng_12	2.756589	0.007724 	0.000007 	0.972470

Αύξηση της cache line (βελτίωση στα miss rate της L1 και της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=1024kB --l1i_assoc=2 --l1d_assoc=2 --l2_assoc=8 --cacheline_size=2048  
specjeng_13	2.648297	0.004024 	0.000007 	0.898667


Δοκιμές για το 5ο benchmark :  
Το συγκεκριμένο benchmark υλοποιεί τη λεγόμενη "μέθοδο Lattice Boltzmann" (LBM) για την προσομοίωση των ασυμπίεστων υγρών στον τρισδιάστατο χώρο. Η εκτέλεση του benchmark με τις default ρυθμίσεις μας δίνει ένα CPI ίσο με 2.623265. Επιπλέον παρατηρούμε ότι έχουμε μεγάλο αριθμό miss rate  στις L1 Data και L2. Αλλάζοντας παραμέτρους της cache μπορούμε να βελτιώσουμε τα στατιστικά αυτά. Με αύξηση της cache line παρατηρούμε ότι τα misses αλλά και το CPI μειώνονται αισθητά καθώς το συγκεκριμένο benchmark φαίνεται πως εκμεταλεύεται καλά την τοπικότητα των δεδομένων. Παρακάτω φαίνονται μερικές δοκιμές και τα αποτελέσματά τους.

Αύξηση assoc για L1 (βελτίωση στα miss rate της L1)  
--l1d_size=64kB --l1i_size=64kB --l2_size=512kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=8 --cacheline_size=64  
speclbm_0	2.631263	0.060971	0.000085 	0.999979

Αύξηση της cache line (βελτίωση στα miss rate της L1)  
--l1d_size=64kB --l1i_size=64kB --l2_size=512kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=8 --cacheline_size=128  
speclbm_1	1.991390	0.030487	0.000087	0.999941 

Αύξηση του μεγέθους της L2 (ίδιο miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=1024kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=8 --cacheline_size=64  
speclbm_2	2.624355	0.060971	0.000085	0.999979

Αύξηση της cache line και αύξηση του μεγέθους της L2 (βελτίωση στo miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=1024kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=8 --cacheline_size=128  
speclbm_3	1.991078	0.030487	0.000087	0.999941

Μείωση assoc για L2 (ίδιο στο miss rate της L2)  
-l1d_size=64kB --l1i_size=64kB --l2_size=512kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=4 --cacheline_size=128  
speclbm_4	1.991390	0.030487	0.000087 	0.999941

Αύξηση του μεγέθους της L2 (ίδιο miss rate της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=2048kB --l1i_assoc=4 --l1d_assoc=4 --l2_assoc=4 --cacheline_size=128  
speclbm_5	1.990438	0.030487	0.000087	0.999941

Μείωση assoc για L1 (αύξηση στα miss rate της L1)  
--l1d_size=64kB --l1i_size=32kB --l2_size=256kB --l1i_assoc=2 --l1d_assoc=2 --l2_assoc=8 --cacheline_size=128  
speclibm_6	1.991623	0.030487	0.000112	0.999799

Μείωση της cache line (αύξηση στα miss rate της L1 και της L2)  
--l1d_size=64kB --l1i_size=32kB --l2_size=256kB --l1i_assoc=2 --l1d_assoc=2 --l2_assoc=8 --cacheline_size=64  
speclibm_7	2.631574	0.060971	0.000094	0.999944

Αύξηση της cache line (βελτίωση στα miss rate της L1 και της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=1024kB --l1i_assoc=2 --l1d_assoc=2 --l2_assoc=8 --cacheline_size=256  
speclibm_8	1.655129	0.015244	0.000090	0.999833

Αύξηση της cache line (βελτίωση στα miss rate της L1 και της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=1024kB --l1i_assoc=2 --l1d_assoc=2 --l2_assoc=8 --cacheline_size=512  
speclibm_9	1.492062	0.007623	0.000088	0.999597

Αύξηση της cache line (βελτίωση στα miss rate της L1 και της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=1024kB --l1i_assoc=2 --l1d_assoc=2 --l2_assoc=8 --cacheline_size=1024  
speclibm_10	1.448663	0.003812	0.000113	0.998681

Αύξηση της cache line (βελτίωση στα miss rate της L1 και της L2)  
--l1d_size=64kB --l1i_size=64kB --l2_size=1024kB --l1i_assoc=2 --l1d_assoc=2 --l2_assoc=8 --cacheline_size=2048  
speclibm_11 	1.374122	0.001907	0.000115	0.996451


Βήμα 3ο  
Συνάρτηση κόστους: Cost = 100 * (l1d_size + l1i_size) + 40 * l2_size + 30 * cacheline_size + 10 * (l1i_assoc + l1d_assoc + l2_assoc) 

Η συνάρτηση κόστους είναι αποτέλεσμα πρόσθεσης κάθε παράγοντα της cache πολλαπλασιασμένο με έναν συντελεστή βαρύτητας. Όσων αφορά το μέγεθος της L1, ο συντελεστής που επιλέξαμε είναι 100 (αυθαίρετος συντελεστής βαρύτητας, σύμφωνα με τον οποίο θα επιλεχθούν και οι υπόλοιποι) διότι στο πρώτο επίπεδο της cache πληρώνουμε περισσότερο από κάθε άλλο επίπεδο παρακάτω. Έτσι ο συντελεστής για το μέγεθος του δευτέρου επιπέδου είναι πιο μικρός και ίσος με 40. Για το μέγεθος της cacheline επιλέξαμε τον συντελεστή βαρύτητας 30 καθώς όσο μεγαλώνει το cacheline, τόσο περισσότερα δεδομένα πρέπει να μεταφέρουμε στην κρυφή μνήμη, γεγονός που κοστίζει αλλά όχι όσο το κόστος από τα μεγέθη των επιπέδων της cache. Τέλος για τα associativity κάθε επιπέδου της cache επιλέξαμε ένα πιο χαμηλό κόστος καθώς αυτά αυξάνουν την πολυπλοκότητα.  
Έχοντας το κόστος για κάθε υλοποίηση της cache μέσω της παραπάνω συνάρτησης αλλά και το τελικό CPI από την εκτέλεση των benchmark μπορούμε να βρούμε τις παραμέτρους της cache που βελτιστοποιούν την απόδοση του συστήματος σε σχέση με το κόστος. Χρησιμοποιώντας ως συνάρτηση αξιολόγησης την Points = 1 / (CPI * Cost), όπου αυξάνεται όσο το κόστος και το CPI μειώνονται, μπορούμε να βρούμε την βέλτιστη αρχιτεκτονική. Παρακάτω δίνονται οι βέλτιστες αρχιτεκτονικές για κάθε benchmark: 
