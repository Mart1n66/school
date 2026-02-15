#' ---
#' title: "Intervaly spolahlivosti"
#' author: "Martin Slatarovic"
#' ---
#' # IS pre $\mu$ ak $\sigma$ pozname
library(latexpdf)
#' Prednaska. K dispozicii mame udaje o dlzke casu, kt stravia pouzivatelia na istej webovej stranke.
#' Najdite 95% IS pre $\mu$, ak $\sigma=3.8$ pozname.
#' Obojstranne, jednostranne, to iste pre 90%
x <- c(48,55,51,62,53,58,60,50,49,57,52,61,54,56,59,53,50,58,55,53)
length(x)
mean(x)
boxplot(x, horizontal = T)
#' ak chceme iba statistiky k tomuto grafu, alebo konkretnu jednu
boxplot(x, plot = F)
boxplot(x, plot = F)$out 
alfa <- 0.05
n <- length(x)
sigma <- 3.8
qnorm(1-alfa/2)
mean(x)+c(-1,1)*qnorm(1-alfa/2)*sigma/sqrt(n)
#' 90% obojstranny, alfa = 0.1
alfa <- 0.1
mean(x)+c(-1,1)*qnorm(1-alfa/2)*sigma/sqrt(n)
#' jednostrannyiba 90%
ISj <- c(mean(x)-qnorm(1-alfa)*sigma/sqrt(n),Inf)
ISj
ISj <- c(-Inf, mean(x)+qnorm(1-alfa)*sigma/sqrt(n))
ISj
#' Vstavanymi funckiami
#' 
#' IS su prepojene s testami, preto prikaz pre testovanie, vo vvystupe je aj IS
#' ak sigma pozname DescTool, Ztest
library(DescTools)
ZTest(x,sd_pop = 3.8)#default je 95%
ZTest(x,sd_pop = 3.8)$conf.int
#' teraz 90%
ZTest(x,sd_pop = 3.8,conf.level=0.9)$conf.int
#' jednostranne
ZTest(x,sd_pop = 3.8,alternative="less")
ZTest(x,sd_pop = 3.8,alternative="less")$conf.int
ZTest(x,sd_pop = 3.8,alternative="greater")$conf.int
#' IS pre $\mu$ ak $\sigma$ nie je zname
#' 
#' ten isty priklad,$\sigma$ nepozname
#' najcastejsie pre prax
#' najprv vzorcami potom cez vstavanu funkciu
#' 
alfa <- 0.05
mean(x)+c(-1,1)*qt(1-alfa/2,n-1)*sd(x)/sqrt(n)
#' este jednostranne
ISj <- c(mean(x)-qt(1-alfa,n-1)*sd(x)/sqrt(n),Inf)
ISj
ISj <- c(-Inf, mean(x)+qt(1-alfa,n-1)*sd(x)/sqrt(n))
ISj
#' t.test je v standartnej kniznici
#' 95%
t.test(x)
t.test(x)$conf.int

#' rovnaky prikaz s rovnakym vystupom je aj v kniznici mosaic 
#' Nakreslime IS, jednoduchhhy graf
#' dolna a horna hranica pre IS
dd <- t.test(x)$conf.int[[1]] #dolna hranica
dd
hh <- t.test(x)$conf.int[[2]]
hh
library(plotrix)
plotCI(1,mean(x),li=dd,ui=hh,main="Is pre strednu hodnotu")
#' IS 90% a jednostranne 95% IS
t.test(x,conf.level=0.9)$conf.int
t.test(x,alternative = "l")$conf.int
t.test(x,alternative = "g")$conf.int
#'# IS pre podmoziny dat
#'
#'Vyukovy dataset data_vyuka.xlsx
data <- readxl::read_xlsx("data_vyuka.xlsx")
new_data <- na.omit(data)
#' neda sa pouzit t.test
t.test(mprij~pohlavie,data=new_data)
#' prikaz z inej kniznice v DescTools
#' je tiez prikaz na IS
MeanCI(x)#DescTool
MeanCI(x,side = "left")
#' Rmisc
library(Rmisc)
CI(x)
#' najdeme IS pre prijem v podmnozinach podla pohlavia
CI_pohlavie <- group.CI(mprij~pohlavie,data=new_data)
CI_pohlavie
CI_pohlavie <- group.CI(mprij~vzdelanie,data=new_data)
CI_pohlavie
#' vizualizacia boxplot 
boxplot(mprij~pohlavie,data=new_data)
boxplot(mprij~vzdelanie,data=new_data)
#'# IS pre disperziu$\sigma^2$
#'
#'najprv podla vzorca potom vstavanymi prikazmi
alfa <- 0.05
c((n-1)*var(x)/qchisq(1-alfa/2,n-1),(n-1)*var(x)/qchisq(alfa/2,n-1))
#' kniznica(EnvStats)
library(EnvStats)
varTest(x)
#' zmena %, jednostranne
varTest(x,conf.level = 0.9)$conf.int#zmena perc
varTest(x,alternative = "l")$conf.int#jednostranne
varTest(x,alternative = "g")$conf.int
#' simulujeme 100x nahodny vyber z normalneho rozdelenia napr.nech $\mu=3$ a $\sigma=1$.
#' pre kazdu simulaciu zratame 95% IS, spocitame kolko je takych co nepokryju strednu hodnotu
k <- 0
for(i in 1:100){
  is <- t.test(rnorm(30,mean=3,sd=1))$conf.int
  if(3>is[[2]]){
    k <- k+1
  }
  if(3<is[[1]]){
    k <- k+1
  }
}
k
#' vyukovay balik TeachingDemos
library(TeachingDemos)
ci.examp(mean.sim=0,method = "t")
run.ci.examp()


