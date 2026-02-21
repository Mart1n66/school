#' ---
#' title: "uvod do R, prvotna statisticka analyza, EDA"
#' author: "Martin Slatarovic"
#' ---
library(latexpdf)
library(latex2exp)
#'
#'# Test pre $\mu$ ak $\sigma$ je zname 
#'
#'K dispozicii mame udaje o dlzke casu (s), ktori stravia pouzivatelia na webovej stranke, 
#'$n=20$ a $\sigma=3.8$
#'na hladine vyznamnosti $\alpha=0.05$ testujte hypotezu, doba casu na stranke je 55s
#' $$h_0 \quad \mu=55 \qquad H_1 \quad \mu \neq 55$$
#' overime normalitu dat graficky aj vypoctovo
cas <- c(48, 55, 51, 62, 53, 58, 60, 50, 49, 57, 52, 61, 54, 56, 59,53,
         50, 58, 55, 53)
qqnorm(cas)
qqline(cas)
#' test normality
shapiro.test(cas)
#' p-value=0.74 > 0.5 takze nezamietame hypotezu $H_0$
#' data su normalne rozdelene
#' najprv podla vzorca, potom vstavanymi funckiami
mi0 <- 55
n <- length(cas)
sigma <- 3.8
alfa <- 0.05
T <- (mean(cas) - mi0)*sqrt(n) / sigma
T
#' RRozhodnutie ci zamietam, nezamietam $H_0$
print(abs(T) <= qnorm(1-alfa/2))
#' nezamietame $H_0$ mozeme tvrdit ze klienti stravia na stranke v priemere 55s 
#' ZTest kniznica DescTools
library(DescTools)
ZTest(cas,mu=55,sd_pop=3.8)
ZTest(cas,mu=55,sd_pop=3.8)$p.value
#' Phodnota=0.72>0.05, teda nezamietame $H_0$
#' testujeme teraz hypotezu ze vydrzia aspon 58 sekund
#' $$H_0 \quad \mu=58 \qquad H_1 \quad \mu<58$$
ZTest(cas,mu=58,sd_pop = 3.8, alternative = "less")
#' Phodnota = 0.00< 0.05, zamietame $H_0$, stravia menej casu ako 58 sekund
#' Ak by bola alternativa greater, teda H1 stravia menej <58
#' $$ H_0 \quad \mu=58 \qquad H_1 \quad \mu>58$$
ZTest(cas,mu=58,sd_pop = 3.8, alternative = "g")
#' Phodnota>0.05, teda nezamietam H_0
#' Zmena hladiny vyznamnosti je iba kvoli IS, lebo plati Phod>alfa nezamietame H_0
#' Nech $\alfa=0.1$
ZTest(cas,mu=55,sd_pop=3.8,conf.level = 0.9)
#' Phodnota=0.724>0.1. nezamietame $H_0$ na danej hladine vyznamnosti
plot(function(x) dnorm(x,0.1),from=-3, to=3, main=TeX("Test pre $\\mu"), ylab="hustota")
#; T=-0.35
abline(v=-0.35,col="blue")
abline(v=qnorm(0.975),col="red")
abline(v=-qnorm(0.975),col="red")
#' t.test v zakladnej kniznici 
#' Riesime ulohu 1 za predpokladu, ze $\sigma$ nepozname
t.test(cas,mu=55)
#' Phodnota = 0.74>0.05 nezamietame $H_0% stravia na stranke v priemere 55s
#' Uloha c.2 stravia aspon 58s
t.test(cas,mu=58,alternative="l")
#' Phodnota=0.00096<0.05 teda zamietame $H_0$
#'# Priklad
#' rodinna firma predava biojablkovu stavu v baleniach 0.5l
#' Po oprave plniacej linky boli namerane hodnoty plnenho objemu v ml. Na hladine vyznamnosti 
#' $\alpha=0.1$ testujte hypotezu, ze linka je dobre  nastavena
#' $$H_0 \quad \mu=500 \qquad H_1 \mu \neq 500$$
jablko <- c(499.2,496.8,502.1,498.5,501,503,500.7,
            501.5,501.8,499.1,500.9,502.2,501.7, 500.4,
            500.2,501.1,499.9,500.2,501.1,500.8,499.3)
#qqplot(jablko)
shapiro.test(jablko)
t.test(jablko,mu=500)
#' Phodnota =0.09<0.1 zamietame $H_0$ linka nie je dobre nastavena na hlad vyznamnosti
#' $\alpha=0.05$ nezamietame
#' priklad
#' 
#' firma ktora vyraba bateria do notebookov tvrdi ze 1 vyrobi do 13min, overte
#' ak mate 20 merani $\alpha=0.05$ stanovte nulovu hypotezu a alter hypo
baterie <- c(12,19,16,13,15,12,14,20,15,19,17,20,
             13,9,11,20,12,19,8,13)
#' $$ H_0 \quad \mu=13 \qquad H_1 \quad \mu>13$$
shapiro.test(baterie)
t.test(baterie, mu=13, alternative = "g")
#' Phodnota=0.02<0.05 zamietame $H_0$ vyroba trva viac ako 13 min
#' 
#' Priklad
#' 
#' Vyrobca tvrdi ze baterky ktore vyraba vzdryia minimalne 19h prevadzky
#' overte tvrdie vyrobcu alfa zostava 0.05
#' $$ H_0\quad \mu=19 \qquad H_1 \quad \mu<19$$ 
baterie1<- c(18.2,19.6,18.6,19.4,17,18.5,18,18.4,19,
             18,17.9,18.1)
t.test(baterie1, mu=19, alternative = "l")
shapiro.test(baterie1)
#' Phodnota=0.006<0.05 zamietam $H_0$ vydrzia menej
#'
#'Priklad
#'
#' pizzeria abc ma na letaku uvedene ze pizzu donesu do 30 min v dat subore pizza su casy dodavok
#' na hladine vyznamnosti $\aplha=0.05$ testujte hypotezu ze ich tvrdenie je pravdive.
pizza <- c(27,25,30,28,29,24,30,26,28,32,
           24,32,31,29,28,29,35,34,30,31)
shapiro.test(pizza)
t.test(pizza,mu=30,alternative="g")
#' Phodnota = 0.9>0.05 nezamietame $H_0$
#' 
#'# test pre disperziu normalneho rozdelenia 
#'
#' V prvom priklade sa tvrdilo ze smerodaj odchylka je $\sigma=3.8$ overte toto tvrdenie 
#' na hlad vyznamnosti $\aplha=0.05$
#' $$ H_0 \quad \sigma^2=3.8^2 \qquad H_1 \quad \sigma^2 \neq 3.8^2$$ 
#' viac kniznic obsahuje test DescTools, EnvStats
library(EnvStats)
varTest(cas,sigma.squared = 3.8^2)
#' graf a oblast kde nezamietam H_0
plot(function(x)dchisq(x,19),from=0, to = 50, main= TeX("Test pre $\\sigma^2$$"),
     ylab="hustota")
abline(v=22.17,col="green")
abline(v=qchisq(0.975,19), col = "red")
abline(v=qchisq(0.025,19), col = "red")
legend("topright",legend = c("hranica krit. oblasti", "statistika"),
       col=c("red","green"),lty=c(1,1))
#'# parove testy
#'
#' k dispozicii su dane casy v sek pocas ktorych vyriesili ziaci kontrolne ulohy  
#' pred a po cviceni z pamatoveho pocitania, tvrdime ze cvic zlepsili schopnost rychlejsie riesit ulohy
pred <- c(87,61,98,90,93,74,83,72,81,75,83)
po <- c(50,45,79,90,88,65,52,79,84,61,52)
#' $$ H_0 \quad \mu_{pred} - \mu_{po} = 0 $$
#' $$ H_1 \quad \mu_{pred} - \mu_{po} < 0 $$
diferencie <- pred - po
diferencie
t.test(pred-po, mu=0, alternative = "l")
t.test(pred, po, mu=0, alternative = "l",paired = T)
#' nezamietame $H_0$, zlepsili sa 

