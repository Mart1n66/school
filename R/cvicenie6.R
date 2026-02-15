#' ---
#' title: "neparametreicke metody"
#' author: "Martin Slatarovic"
#' ---
library(latexpdf)
#'# testy nahodnosti
#'
#' testujem, ci merania su nahodne a nezavisle
#'# Wald Wolfovitzov test, test serii
#'
#' $$H_0\quad \text{data su nahodne} \qquad H_1 \text{nie su nahodne}$$
library(randtests)
#' linka mhd prejde v rannej spicke trasu priemernou rychlostou 8km/h, navrhla sa  nova trasa, 
#' chceme zrychlit rychlost, 10 dni sme merali testujte nahodnost merani
rychlost <- c(7.7,7.8,8.5,7.8,7.9,9,7.5,8.2,9.3,8.1)
mean(rychlost)
plot(rychlost,type='b')
runs.test(rychlost,plot=T)
#' phodnota > .05 nezamietam H_0, su nahodne
runs.test(rychlost,alternative = "left.sided")
runs.test(rychlost,alternative = "right.sided")
#'# test kritickych bodov, turning point test 
turning.point.test(rychlost)
#' phodnota=0.78>0.05, nezamietame H_0
#' 
#' Neparametricke testy, ako ekvivalent k parametrickym testom, ziadne podmienky na data nekladieme
#' paramet: test pre strednu hodnotu
#' neparamet: test pre median
#' 2 testy-znamienkovy a druhy je wilconov test
#' $$H_0\quad \text{Me=c} \qquad H_1\quad \text{Me!=c}
#'# Znamienkovy test
#'
#' tim pre kontrolu kvality, urcil ze prijatelny median kvality pre vystup gen AI modelu je 7.5
#' overte ci sa lisi kvalita objednavky ci co
ai <- c(7.5,6.8,7.2,8.1,7,6.5,7.9,8.5,6.9,7.5,7.3,6.6,7.8,6.2,7.4)
mean(ai)
library(BSDA)
SIGN.test(ai,md=7.5)
#' phodnota >0.05 nezamietame H_0, je porovnatelna
SIGN.test(ai,md=7.5,alternative = "g")
#' nie lepsia iba porovnatelna
#'# wilcoxonov test, signed rank test 
#'
#' potrebujeme overit symetreiu dat, ak to nie j =e splnene, tak znamienkovy test
#' Boxplot, sikmost, test-opatrne
#' testujte aj wilcoxonovym testom po overeni podmienok
boxplot(ai, horizontal = T)
moments::skewness(ai) #cisla blizke k 0 idu k symetrii ci co 
moments::agostino.test(ai)
#' este jedna charaktresit
pastecs::stat.desc(ai,norm = T)
#' ak abs(skw.2SE)>1 tak sa povazuju za zosikmene nejako podmienky su splnene tak mozeme wilcoxa
wilcox.test(ai,mu=7.5)
#' phodnota > 0.05 nezamietame H_0 median je 7.57
#' pripomienka, parametricke testy 
shapiro.test(ai)#normalita dat
t.test(ai,mu=7.5)
#' aj parametricky test nezamietam len tam je hypotezaz o strednej hodnote
#' priklad
#' 
#' pri tradicnom opracovani suc sa dosahuje median kval 4.4 navrhla sa lacnejsia jednoduch metod test 
#' hypotz ze ich kval vlast je aspon 4
kvalita <- c(4.5, 4.3, 4.1, 4.9, 4.6, 3.6, 4.7, 5.1, 4.8, 4, 3.7, 4.4, 4.9, 4.9, 5.2, 5.1, 4.7, 4.9, 4.6,4.8)
mean(kvalita)
boxplot(kvalita)
moments::skewness(kvalita)
pastecs::stat.desc(kvalita)
#install.packages("lawstat")
library(lawstat)
lawstat::symmetry.test(kvalita)
#' symetricke
#' alternativa zo zadania je ze menej ako 4.4 
wilcox.test(kvalita,mu=4.4,alternative = "less")
#' pohodnta je > 0.05 nezamietam H_0 teda je aspon 4.4
#'# Parove testy 
#' 
#' su dane casy v sekundach kde ziaci riesili ulohy z pamat pocitania pred a po spec cvic, su rychlejsi ?
pred <- c(87,61,98,90,93,74,83,72,81,75,83)
mean(pred)
po <- c(50,45,79,90,88,65,52,79,84,61,52)
pred-po
SIGN.test(pred,po,paired=T,alternative="less")
#' phodnota je > 0.05, zlepsili sa studenti
boxplot(pred-po)
moments::skewness(pred-po)#vysledok sa blizi k 0 takze budu symetricke, vidno aj na grafe o riadok hore 
wilcox.test(pred-po,alternative = "l")
wilcox.test(pred,po,paired=T,alternative = "l")
#'# dvojvyberovy wilcoxonov test 
#'
#' $$ H_0 \quad F_X=F_Y$$
#' ak su vzorky vyrazne odlisne tak kolmogorovo smirnovov test
#' z produkcie dvoch firiem sme vybrali n=10 m=8 kusov vyrobkov, hodnotili sme kvalitu pridelenim, testujte 
#' kvalitu o rov kval
firma1 <- c(420,560,600,490,550,570,340,480,510,460)
mean(firma1)
firma2 <- c(400,420,580,470,470,500,520,530)
mean(firma2)
boxplot(firma1,firma2)
qqplot(firma1,firma2)
abline(0,1,col="red")
#' este rovnost disperzii, neparametricky test
#' levene test,musime upravit data
zdruzeny <- data.frame("body"=c(firma1,firma2),
                       "firma"=rep(c(1,2),
                                   times=c(1,8)))
zdruzeny
car::leveneTest(zdruzeny$body,zdruzeny$firma)
#' phodnota je > 0.05, vacsie disperzie,
#' wilcox
wilcox.test(firma1,firma2)
ks.test(firma1,firma2)
#' testy oboje potvrdili ze sa nelisia(kval vlastnosti), phodnoty boli > 0.057
#'# kruskal wallisov test
#'
#' neparametricke anova
#' 
#' priklad studia skuma vplyv prac prostr na uroven unavy zamestnancov, vzorka odpovedala 1-10, dane tab
data <- data.frame("unava" = c(7,8,5,9,4,3,6,5,4,2,3,1),
                   "prostredie" = rep(c(1,2,3),times=c(4,5,3)))
data
boxplot(data$unava~data$prostredie)
car::leveneTest(data$unava,data$prostredie)
kruskal.test(data$unava,data$prostredie)
#' phodnota je 0.01 < 0.05, zamietame H o rovnosti rozdeleni, prostredie ma vplyv na uroven unavy 
#' nasleduje post test
#' dunnov test
library(dunn.test)
dunn.test(data$unava,data$prostredie,
          altp = T, list = T)
#' z vystupu vidime ze odlisnu si triedy 1 a 3 tam je phdonota < 0.05 to v zatvorke
