#' ---
#' title: "uvod do R, prvotna statisticka analyza, EDA"
#' author: "Martin Slatarovic"
#' ---
#' 
#' Nastavenie pracovneho adresara, v nom su aj vyukove data
#' moznosti cez Files(vpravo dole), Session choose direcitory...
#' uzitocne prikazy pre pracu so subormi a dresarmi (wd)
#' 
#' library(readxl); 
#' library(psych); 
#' library(Hmisc); 
#' library(pastecs)
#' library(moments); 
#' library(DescTools); 
#' library(EnvStats); 
#' library(car)
#' library(BSDA); 
#' library(dunn.test); 
#' library(effectsize); 
#' library(lawstat)
#' library(randtests)
#' 
#' Čo potrebuješ urobiť?,Ktorý súbor otvoriť?,Kľúčové funkcie
# "Načítať dáta, zistiť chyby, základný popis",cvicenie1.R,"read_xlsx, sum(is.na()), mean, median, sd, skewness"

#Intervaly spoľahlivosti (IS),cvicenie2.R,"t.test(...)$conf.int, MeanCI, varTest (pre rozptyl)"

#"Testy pre 1 výber (napr. ""rovná sa priemer 100?"")",cvicenie3.R,"shapiro.test (normalita), t.test, ZTest"

#Testy pre rozptyl (1 výber),cvicenie4.R,varTest (chi-kvadrát test pre rozptyl)

#Porovnanie 2 skupín a ANOVA (Parametrické),cvicenie5.R,"var.test (zhoda rozptylov), t.test (2 výbery), aov (ANOVA), TukeyHSD"

#Neparametrické testy (Keď dáta nie sú normálne),cvicenie6.R,"runs.test (náhodnosť), wilcox.test, SIGN.test, kruskal.test"



getwd()#pracovny adresar
dir()#ake subory su v adresari
list.files()#to iste
#' kedze pracujeme s datami, prikazy pre import dat
#' .xlsx, csv, importovat subory .xlsx
#' znamena nacitat kniznicu read_xl
library(readxl) # alt-
data <- read_xlsx("data_vyuka.xlsx")#xlsx
diabetes <- read.csv("diabetes.csv")
#' tabulka dat
View(data)
View(diabetes)
#' prikazy na preskumanie struktury dat, 
str(data)#struktura dat
names(data)#stlpce
head(data)#prvych 6
#' Chybajuce data
#' 
#' V rku reprezentovane NA, kniznice, ktore sluzia k zisteniu strukt
#' z hladiska chybajucich dat a doplneniu chybajuich
#is.na(data)
sum(is.na(data))#pocet chybajucich
sum(is.na(data$pohlavie))#chybajuce v stplci pohlavie
#' kninica mice, Amelia
library(mice)
md.pattern(data)#vizualizacia chybajucich dat
library(Amelia)
missmap(data)
#'chybajuce vynechame
new_data <- na.omit(data)
str(new_data)
#' vhodne kniznice pre prvotnu analyzu
library(psych)
library(Hmisc)
library(FSA)
library(pastecs)
library(moments)
library(ie2misc)
library(modeest)
#' charakteristiky polohy
#' 
#' minimum, maximum, priemer, median, modus
#' tabulky pocetnosti, triednych pocetnosti
#' pre jeden stlpec napr pre mrpij
plat <- new_data$mprij
table(plat) # tabulka pocetnosti
prop.table(table(plat))#relat pocetnosti
cumsum(table(plat))

#' tabulka triednych pocetnosti, prikaz
#' pre histogram, s upresnenim plot-F
hist(plat)

#'hist(plat, plot=F)
tp <- hist(plat,plot=F)
tp$breaks
tp$counts

#' poloha min max mean(odhad strednej hodnoty, priemer), median
min(plat)
max(plat)
mean(plat)
median(plat)
mfv(plat)#modus
#' este zopar uzitocnych prikazov
sort(plat)#usporiadanie
sort(plat)[15]#15ta v usporiadani
sum(plat==1200)#pocet s platom 1200
sum(plat>1200)#pocet s vacsie ako 1200
sum(new_data$vek<40)#pocet s vekom mensim ako 40r

#' geometricky a harm priemer
#' iba tvar prikazu, tu nema zmesel ratat
geometric.mean(plat)
harmonic.mean(plat)
fivenum(plat)
quantile(plat)
quantile(plat,0.1)
#' charakteristiky rozptylu
#'
#' variacne rozpatie, odhad disperzie, smerodajnej odchylky, kvarilove rozpatie -IQR, priemerna 
#' absolutna odchylka
max(plat)-min(plat)
range(plat)
var(plat)#odhad disperzie
sd(plat)#smerodajna odchylka, odmocnina z toho predtym
IQR(plat)
madstat(plat)#priemerna absolutna odchylka
mad(plat)
#' ine charakteristiky
#' 
#' sikmost, spicatost, normalne rozdelenie
#' subory maju sikmost=0, spicatost=3
#' pozor na kniznicu, z ktorej budeme volat prikaz
skew(plat)#psych
skewness(plat)#modeest
#' pouzivat kniznicu moments
moments::skewness(plat)
kurtosi(plat)#sikmost-3
kurtosis(plat)#radsej toto
#' jeden dolezity graf, krabicovy
#' Box Whisker plot
boxplot(plat,horizontal=T)#povodne bez horizontat=T
#' simulacia symetrickych a nesymetrickych dat sikmost a spicatost
par(mfrow=c(1,1))#nastavenie kreslenia, iba do jedneho okna
s1 <- rnorm(1000,mean=0,sd=1)
hist(s1)
par(mfrow=c(1,2))
hist(s1)
boxplot(s1,horizontal=T)
moments::skewness(s1)
kurtosis(s1)
#' chi kvadrat rozdeleni co je nesymetricke
s2 <- rchisq(100,df=5)
hist(s2)
boxplot(s2,horizontal=T)
moments::skewness(s2)
kurtosis(s2)
#' tabulky sumarnych statistik
summary(plat)#base
Hmisc::describe(plat)#Hmisc zevraj inak robilo cez psych

