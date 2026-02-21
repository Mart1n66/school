#' ---
#' title: "Rozdelenia pravdepodobnosti"
#' author: "Martin Slatarovic"
#' ---
library(latex2exp)
library(latexpdf)
#' Prikazy pre rozdelenia pravdepodobnosti
#' *nazov rozdelenia
#' *-d, $P(X=i)=p_i$
#' *-p, $P(X\leq i), ak pridame lower.tail=F,$P(X>i)$
#' *-q, kvantil
#' *-r, random, pseudonahodne cislo
#' Binomicke rozdelenie
#' 
#' Ma dva paramerte, n-pocet pokusov, p-pravdepodobnost
#' sledovaneho javu v jednom pokuse
#' *binom(...,n,p)
#' 
#' Ucinnost antibiotika je 80%, podavame ho 10 pacientom.
#' n=10, p=0.8
#' Vypocitajte tieto pravdepodobnosti.
#' Vsetci sa vyliecia $P(X=10)$
dbinom(10,10,0.8)
#'Prave 7 sa vylieci
dbinom(7,10,0.8)
#'Najviac sa vylieci 8 $P(X\leq 8)$
pbinom(8,10,0.8)
#'Aspon 5 sa vyloeci $P(X\geq 5)=1-P(X\leq 4)$
1-pbinom(4,10,0.8)
pbinom(4,10,0.8, lower.tail = F)
#'Generujte nahodne cislo z tohto rozdelenia
rbinom(1,10,0.8)
#' Tabulka rozdelenia pravdepodobnosti a graf rozd. pravd.
xB <- 0:10
hustotaB <- dbinom(xB,10,0.8)
(tabulkaB <- data.frame(hodnota=xB, pravdepodobnost=hustotaB))

barplot(tabulkaB$pravdepodobnost, main="Binomicke rozdelenie", xlab = "hodnota",ylab = "pravdepodobnost", col = "blue", names.arg = xB)
#' Distribucna funkcia
distB <- pbinom(xB,10,0.8)
(tabulkaB1 <- data.frame(hodnota=xB, kumulovana=distB))
barplot(tabulkaB1$kumulovana, main="Binomicke rozdelenie", xlab = "hodnota",ylab = "kumulovana", col = "blue", names.arg = xB)
data <- rbinom(10000,10,0.8)
plot(ecdf(data), main="Empiricka distribucna funkcia", ylab = "distribucna funkcia")
#'# Hypergeometricke rozdelenie
#'
#'Ma tri parametre, m-pocet objektov so sledovanou vlastnostou,
#'n-pocet bez tejto vlastnosti, k- pocet objektov, ktore vyberame
#'*hyper(...,m,n,k)
#'# Priklad
#'
#'Student sa nauci na skusku 12 z 20 otazok. Test obsahuje 5 otazok. 
#'Vypocitajte tieto pravdepodobnosti:
#'Student urobil skusku(Zodpovie aspon 3)
#'sledovana vlastnost- vie odpoved
#'$P(X\geq 3)=P(X>2)$
phyper(2,12,8,5,lower.tail = F)
#' Student dostane A(zodpovie vsetko)
dhyper(5,12,8,5)
#' Student neurobi skusku $P(X\leq 2)$
1-phyper(2,12,8,5,lower.tail = F)
#'Tabulka a graf rozdelenia pravdepodobnosti
xH <- 0:5
hustotaH <- dhyper(xH,12,8,5)
(tabulkaH <- data.frame(hodnota=xH, pravdepodobnost=hustotaH))

barplot(tabulkaH$pravdepodobnost, main="Hypoergeometricke rozdelenie", xlab = "hodnota",ylab = "pravdepodobnost", col = "blue", names.arg = xH)
#'# Geometricke rozdelenie
#'
#'pocet uspechov do prveho neuspechu, parameter je p-pravdep. uspechu
#'*geom(..t.,prob=p)
#'# Priklad
#'
#'Testujeme novy softverovy modul, test prejde uspesne, bez chyby s p=0.85. Neuspech nastava
#'ak test najde kriticku chybu
#'Aka je p, ze modul prejde uspesne az po dvoch neuspechoch
dgeom(2,prob = 0.85)
#' Aka je p, ze max 3 chyby, kym test bude uspesny $P(X\leq 3)$
pgeom(3,prob = 0.85)
#' Aky je max poocet chyb, ktory ocakavame s 95% istotou $P(X\leq k)\geq 0.99$
qgeom(p=0.99,prob=0.85)
#' Tabulka a graf rozdelenia p pre prvych 5 hodnot
xG <- 0:5
hustotaG <- dgeom(xG,prob=0.85)
(tabulkaG <- data.frame(hodnota=xG, pravdepodobnost=hustotaG))

barplot(tabulkaG$pravdepodobnost, main="Geometricke rozdelenie", xlab = "hodnota",ylab = "pravdepodobnost", col = "blue", names.arg = xG)
#'# Poissonovo rozdelenie
#'
#'Ma jediny prameter $\lambda$- stredna hodnota. Pocet slov za  jednostku casu
#'*pois(...,labmda)
#'
#'Prklad
#'Na samoobsluznu linku pride za hodinu 20 ludi. vypocitajte p
#'V priebehu 15min pride 1 clovek.
#'Prepocet
lambda <- 20/60*15
dpois(1,lambda)
#' 10min 10 ludi
lambda <- 20/60*10
#' $P(X\geq 10)=P(X>9)$
ppois(9,lambda,lower.tail = F)
#' Tabulka a graf rozdelenia pravdepodobnosti
xP <- 0:40
hustotaP <- dpois(xP,20)
(tabulkaP <- data.frame(hodnota=xP, pravdepodobnost=hustotaP))

barplot(tabulkaP$pravdepodobnost, main="Poissonovo rozdelenie", xlab = "hodnota",ylab = "pravdepodobnost", col = "blue", names.arg = xP)
#'# Spojite rozdelenia pravdepodobnosti
#'
#'#Normalne rozdelenie pravdepodobnosti
#'
#'Ma dva parametre, strednu hodnotu $\mu$ a smerodajnu odchylku $\sigma=\sqrt{D(X)}$
#'*norm(...,mean=mi, sd=sigma)
#'
#'# Priklad
#'Zivotnost bateriek do telefonov sa riadi normalnym rozdelenim so strednou hodnotou 8 rokov
#'a sd 2 roky.
#'Rieste tieto ulohy:
#'Kolko % bateriek treba vymenit skor ako 7.5 roka
#'$P(X\leq 7.5)$
pnorm(7.5, mean=8,sd=2)
#' Kolko % vydrzi v rozpati 7-9 rokov
pnorm(9, mean=8,sd=2)-pnorm(7, mean=8,sd=2)
#' %, ktore vydrzi viac ako 10
pnorm(10, mean=8,sd=2, lower.tail = F)
#' Za aku dobu zivotnosti sa mozno zarucit na 90%
qnorm(0.1,8,2)
qnorm(0.9,8,2,lower.tail = F)
#'# Histogram a hustota rozdelenia N(0,1)
xx <- rnorm(500,0,1)
hist(xx, freq = F,ylim=c(0,0.5), col = "blue")
lines(sort(xx),dnorm(sort(xx),0,1),col = "red")
#'# Exponencialne rozdelenie 
#'
#'Doby zivotnosti vyrobkov, doba medzi pouŕuchami 
#'jediny parameter $\lambda$ pricom plati $E(X)=\frac{1}{\lambda}$
#'*exp(...,rate=E(X))
#'Dlzka zivotnosti PC v pocitacivej ucebni je 2 roky E(X)=2. Vypocitajte p:
pexp(1,rate=1/2,lower.tail = F)
#'Najviac 5 rokov
pexp(5,1/2)
#' za aku zivotnost by sa zarucili s p 0.05
qexp(0.05,1/2,,lower.tail = F)
#'# Hustota exp. rozdelenia pre rozne $\lambda$
x <- 0:5
plot(function(x) dexp(x,rate = 1/2), xlim = c(0,5),ylim = c(0,2),ylab = "hustota", main="Exponencialne rozdelenie" )
plot(function(x) dexp(x,rate = 1/5), xlim = c(0,5),ylim = c(0,2),ylab = "hustota", main="Exponencialne rozdelenie", col = "red", add=T)
plot(function(x) dexp(x,rate = 1/3), xlim = c(0,5),ylim = c(0,2),ylab = "hustota", main="Exponencialne rozdelenie", col = "blue", add=T)
legend("topright",legend=c("Exp(1/2)","Exp(1/5)","Exp(1/3)"), col=c("red","blue","green"),lty = c(1,1),cex=0.5)
#'# Nejaky prklad na porovnanie hypergeom a bin rozdelenia
hustotaB <- dbinom(xH,5,12/20)
spolu <- rbind(hustotaH, hustotaB)
spolu
barplot(spolu, beside=T ,main="Hypergeometricke a Binomicke rozdelenie", xlab = "hodnota", ylab = "pravdepodobnost", col = c("blue", "red"), names.arg = xH)
