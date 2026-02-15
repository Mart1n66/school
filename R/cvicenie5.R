#' ---
#' title: "Dvojvyberove testy"
#' author: "Martin Slatarovic"
#' ---
library(latexpdf)
#' testujeme zw stredne hodnoty dboch nezavilych vyberov sa rovnaju normalita dat musi byt splnena
#'# priklad 1 rovnost disperzii
#' sledujeme odolnost voci svetlu pre dva druhy plastickych hmot. odolnost v dnoch sme zaznamenali. 
#' testujte hypotezu ze odolnost voci svetlu je rovnaka
prvy <- c(85,87,92,80,84,86)
druhy <- c(89,89,90,84,92)
shapiro.test(prvy)
shapiro.test(druhy)
#' graficky
boxplot(prvy,druhy,horizontal = T)#outliers
boxplot(prvy,druhy,horizontal = T,range=0)#uz to vyzera lepsie
#' testu o rovnosti strednych hodnot predchadza test, ci disperzie sa rovnaju
var.test(prvy,druhy)
#' disperzie mozno povazovat za rovnake nasleduje test za rovnosti disperzii
#' $$H_0 \quad \mu_{prvy}=\mu_{druhy}$$
t.test(prvy,druhy,paired = F,var.equal = T)#ak by sme testovali rozdiely o delta tak este nieco pridame neviem co
#' phhodnota = 0.17 > 0.05 nezamietame $H_0$ odolnost je rovnaka
#' priklad 2 nerovnost disperzii
#' firma nakupuje ochranne pracovne prostriedky od dodavatela AA, BB. Testujte ze dlzky dodavok tovaru su rovnake
aa <- c(10,12,15,25,18,20,15,25,30)
bb <- c(15,15,18,10,16,12,15)
boxplot(aa,bb,horizontal = T)
shapiro.test(aa)
shapiro.test(bb)
var.test(aa,bb)
#' phodnota = 0.03 < 0.05 zamietame $H_0$. Disperzie sa nerovnaju vyberieme spravny test pre stredne hodnoty
t.test(aa,bb,paired = F,var.equal = F)
#' phodnota=0.06>0.05,nezamietame $H_0$.
#' Dlzky dodavok mozno povazovat za rovnake.
#' ANOVA, jednofaktorova, One way
#' testujeme ze stredne hodnoty viac ako dvoch vyberov sa rovnaju oproti alternative ze existuje aspon 1 rozna dvojica
#' k dispozicii mame udaje o priemerno prijme pre 3 podmnoziny vzdelanostnych skupin 
#' (faktor-druh vzdelania, tri urovne ZS SS VS)
#' overte podmienky anova a testujte hypotezu ze priemerny prijem pre rozne stupne vzdelania je rovnaky
data <- readxl::read_xlsx("data_vyuka.xlsx")
new_data <- na.omit(data)
str(new_data)
#' normalita v triedach 
tapply(new_data$mprij,new_data$vzdelanie,shapiro.test)
#' podmienka normality dat je splnena
#' rovnost disperzii, bartlettov test
bartlett.test(new_data$mprij,new_data$vzdelanie)
#' aj podmienka rovnosti disperzie je splnena.
#' vizualizacia
boxplot(new_data$mprij~new_data$vzdelanie,
        xlab = "vzdelanie", ylab = "prijem")
library(ggplot2)
library(vioplot)
library(RColorBrewer)
library(ggpubr)
pomoc <- data.frame(new_data$vzdelanie,
                    new_data$mprij)
ggline(pomoc,x = "new_data.vzdelanie",
       y = "new_data.mprij", add = c("mean_ci",
                                     "violin",
                                     "jitter"))
#'# ANOVA
#' vyzaduje faktorizovat to co rozdeluje do skupin
vzdelanie <- factor(new_data$vzdelanie)
anova <- aov(new_data$mprij~vzdelanie)
summary(anova) # pod pr(>F) je pvalue to si odniest a milujem mastu
#' phodnta je skoro 0 to znamena ze triedy sa odlisuju, zamietame hypotezu o nevyznamnosti faktora
#' vzdelanie ma vplyv na vysku prijmu
#' aky velky je vplyv faktora, zistime ked vypocitame mieru efektu
library(effectsize)
eta_squared(anova)
#' 0.62 znamena vysoky efekt faktora vzdelanie
#' potrebujeme zostit, ktore dvojice
#' tried su vyznamne odlisne,post hoc testy
#' Tukey a Scheffe test
TukeyHSD(anova)
#' podla tabulky a phodnot neodlisuje sa 1-2 a odlisuju sa 1-3 a 2-3 
plot(TukeyHSD(anova))
library(DescTools)
ScheffeTest(anova)
plot(ScheffeTest(anova))
#'# dvojfaktorova analyza rozptylu
#'
#'Data sa rozdeluju do podmnozin podla
#'dvoch znakov, zatial neuvazujeme interakcie
#'Datovy subor anova.xlsx
#'Traja laboranti (faktor) urobili opakovane
#'merania na pristrojoch (faktor)
#'Testuje hypotezy,ze tie
#'nemaju vplyv na merania 
anova1 <- readxl::read_xlsx("anova1.xlsx")
#' faktorizzujeme
laborant <- factor(anova1$laborant)
pristroj <- factor(anova1$pristroj)
#' Grafy vzhladom na jednotlive faktory
par(mfrow=c(1,2))
boxplot(anova1$deg~anova1$laborant,
       xlab = "laborant", ylab = "deg")
boxplot(anova1$deg~anova1$pristroj,
        xlab = "pristroj", ylab = "deg")
tapply(anova1$deg,list(anova1$laborant,
                       anova1$pristroj),
       function(x) shapiro.test(x)$p.values)
#' overovat rovnost disperzii nebudeme ale treba
an1 <- aov(anova1$deg~laborant+pristroj)
summary(an1)
#' prvy raidok phodnota je 0.001 < 0.05 tak faktor laborant je nenulovy 
#' alebo statisticky vyznamny ma vplyv na vysledky merani
#' druhy riadok phodnota je 0.0006 < 0.05 aj faktor typ pristroja je stat. vyznamny ma vplyv na vysledky mrenia
#'Efect size  velka miera vplyvu
eta_squared(an1)
#'Post testy
TukeyHSD(an1)
#'laborant,odlisne su a-b-,a-c
#'pristroj,odlisne su A-B,A-D,C-D
plot(TukeyHSD(an1))
ScheffeTest(an1)
#'uvazujme teraz interakcie
an2 <- aov(anova1$deg~laborant*pristroj)
summary(an2)
#' interakcie su statisticky nevyznamne, preto setrenie a interpretacia ako hore
#' vyznamne interakcie
#' testujem rychlost eshopu, ulohou je zistit ako sa na spracovanie pouzivatelskej poziadavky (cas v s)
#' meni v zavislosti od dvoch faktorov, latencie siete (3 urovne) a zlozitost UI
anova3 <- readxl::read_xlsx("anova_interakcie.xlsx")
str(anova3)
an3 <- aov(cas~latencia*uiz,data=anova3)
summary(an3)
# grafy interaction.plot
par(mfrow=c(1,1))
interaction.plot(
  x.factor = anova3$latencia,
  trace.factor = anova3$uiz,
  response = anova3$cas,
  fun = mean,
  type = "b",
  col = c("blue","red"),
  pch = c(19,17),
  trace.label = "Typ UI",
  xlab = "Latencia",
  ylab = "Cas(s)",
  main = "Interakcie a latencie UI"
)
