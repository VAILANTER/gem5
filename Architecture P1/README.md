## ΑΡΧΙΤΕΚΤΟΝΙΚΗ 1η ΕΡΓΑΣΙΑ  
#### ΟΜΑΔΑ 43
#### ΤΣΟΥΡΑΚΑΣ ΔΗΜΗΤΡΙΟΣ 9042  
#### ΑΘΑΝΑΣΙΑΔΗΣ ΧΡΗΣΤΟΣ 9092  

### Εισαγωγή στον εξομοιωτή gem5

**1.2.**
Στο αρχείο **starter_se.py** δίνονται όλες η πληροφορίες για το σύστημα που πρόκειται να εξομοιωθεί. Δίνονται τα _τρία_ μοντέλα cpu που μπορούν να χρησιμοποιηθούν (**AtomicCPU, MinorCPU, HPI**). Στο αρχείο ορίζεται η κλάση **SimpleSeSystem** στην οποία θέτονται παράπετροι όπως το μήκος της μνήμης cache, το σύστημα αναφοράς τάσης και το σύστημα αναφοράς συχνότητας επεξεργαστή. Οι παράμετροι αυτοί φαίνονται και στα αρχεία **config.ini** και **config.json** (time_sync_period=100000000000 cache_line_size=64 voltage=3.3 και "voltage": [3.3] 
"cache_line_size": 64 "time_sync_period": 100000000000 αντίστοιχα). Μέσα στη main και σαν default σύστημα εξομοίωσης υπάρχει το atomic 
το οποίο θέτει τα εξής χαρακτηριστικά στο σύστημα συχνότητα επεξεργαστή 4GHz , αριθμός πυρήνων 1 ,τεχνολογία μνήμης DDR3 @1600MHz 8x8,
καναλια μνημης 2 ,μεγεθος μνημης 2 GigaByte ,memory rank none

**3.**
Ο προσομοιωτής gem5 χρησιμοποιεί τα εξής in-order cpu μοντέλα: MinorCPU, SimpleCPU και HPI.

Το **MinorCPU** είναι ένα in-order μοντέλο με fixed pipeline αλλά διαμορφώσιμες δομές δεδομένων και συμπεριφορά εκτέλεσης (execute behavior).
Προσομοιώνει επεξεργαστές με αυστηρή in-order συμπεριφορά εκτέλεσης.
Περιέχει ένα container για τον αγωγό (pipeline), εντολή Fetch1 για την ανάκτηση δεδομένων απ τις γραμμές της cache μνήμης με διεπαφή 
IcachePort για την l-cache, Fetch2 για την αποσύνθεση της εντολής, Decode στάδιο για την αποκωδικοποίηση micro-op και στάδιο της 
εκτέλεσης της εντολής (Execute) και διεπαφής της μνήμης δεδομένων με LSQ ουρά αποθήκευσης για memory ref. instructions.

Το **SimpleCPU** μοντέλο είναι ένα καθαρά λειτουργικό in-order μοντέλο για περιπτώσεις που ένα λεπτομερές μοντέλο δεν είναι απαραίτητο. 
Χωρίζεται σε τρεις κατηγορίες: _BaseSimpleCPU_, _AtomicSimpleCPU_ και _TimingSimpleCPU_.  

1)Το **BaseSimpleCPU** ορίζει λειτουργίες για τον έλεγχο των interrupts, τη ρύθμιση του fetch request, τον χειρισμό post-execute δράσεων, 
και τη προώθηση του υπολογιστή στην επόμενη εντολή. Παρόλα αυτά δεν μπορεί να τρέξει μόνο του και πρέπει να χρησιμοποιήσει μία απ τις 
κλάσεις, είτε το AtomicSimpleCPU είτε το TimingSimpleCPU.

2)Το **AtomicSimpleCPU** είναι έκδοση του SimpleCPU που χρησιμοποιεί πρόσβαση σε ατομική μνήμη (atomic memory accesses). Χρησιμοποιεί τις 
εκτιμήσεις λανθάνοντος χρόνου (latency) απ τις ατομικές προσβάσεις για να υπολογίσει το συνολικό χρόνο πρόσβασης στη cache. Προέρχεται 
απ το BaseSimpleCPU και υλοποιεί λειτουργίες για ανάγνωση και εγγραφή μνήμης, καθώς επείσης και τη μέτρηση tick, η οποία καθορίζει τι 
συμβαίνει σε κάθε κύκλο CPU. Ορίζει το port που χρησιμοποιείται για να συνδεθεί η μνήμη και συνδέει τη CPU με την cache.
tick()-->setupFetchRequest()/translateAtomic()-->sendAtomic()-->preExecute()-->execute()-->postExecute()

3)To **TimingSimpleCPU** είναι η έκδοση του SimpleCPU που χρησιμοποιεί timing memory accesses. Σταματάει στις προσβάσεις κρυφής μνήμης και περιμένει το σύστημα μνήμης να ανταποκριθεί πριν προχωρήσει. Όπως και το AtomicSimpleCPU, το TimingSimpleCPU προέρχεται επίσης από το 
SimpleCPU και εφαρμόζει το ίδιο σύνολο λειτουργιών. Ορίζει τη θύρα που χρησιμοποιείται για να συνδεθεί στη μνήμη και συνδέει τη CPU με 
την κρυφή μνήμη. Ορίζει επίσης τις απαραίτητες λειτουργίες για τον χειρισμό της απόκρισης από τη μνήμη στα acceses που έχουν σταλεί.

Το **High-Performance In-order CPU (HPI)** αντιπροσωπεύει έναν σύγχρονο in-order Armv8-A επεξεργαστή. Το pipeline του χρησιμοποιεί τα ίδια 4 στάδια όπως ο MinorCPU. 
(Πληροφορίες από [gem5](www.getm5.org))

Το πρόγραμμα που υλοποιήσαμε σε C(Dice.c), είναι ένα πολύ απλό πρόγραμμα στο οποίο "ρίχνουμε" ένα ζάρι 50000 φορές, μετράμε πόσες φορές έρχεται κάθε αποτέλεσμα (1,2,3,4,5,6) και το εκτυπώνουμε.

Εκτελώντας το παραπάνω πρόγραμμα στον gem5 με μοντέλο cpu τη **MinorCPU** πήραμε τα εξής στατιστικά:  
+ sim_ticks  3570030000 # Number of ticks simulated  
+ sim_seconds  0.003570 # Number of seconds simulated  
	
Εκτελώντας το παραπάνω πρόγραμμα στον gem5 με μοντέλο cpu τη **TimingSimpleCPU** πήραμε τα εξής στατιστικά:  
+ sim_ticks  8199441000  
+ sim_seconds  0.008199  
	
Αλλάζοντας την συχνότητα σε **3GHz**, στην **MinorCPU** έχουμε:  
+ sim_ticks  2387693583  
+ sim_seconds  0.002388  
	
Αλλάζοντας την συχνότητα σε **3GHz**, στην **TimingSimpleCPU** έχουμε:  
+ sim_ticks  5470539318   
+ sim_seconds  0.005471    
	
Παρατηρούμε ότι καθώς αυξάνουμε την συχνότητα του ρολογιού μειώνεται και ο χρόνος εκτέλεσης (κάτι που είναι προφανές). Συγκρίνοντας, 
τώρα, τα δύο μοντέλα παρατηρούμε ότι η εκτέλεση του προγράμματος με τη MinorCPU γίνεται γρηγορότερα από ότι με τη TimingSimpleCPU. 
Αυτό οφείλεται στο γεγονός ότι η TimingSimpleCPU έχει πιο πολύπλοκη αρχιτεκτονική από τη MinorCPU και σταματάει στις προσβάσεις κρυφής 
μνήμης και περιμένει το σύστημα μνήμης να ανταποκριθεί πριν προχωρήσει.
