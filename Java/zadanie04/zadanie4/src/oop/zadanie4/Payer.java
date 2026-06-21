package oop.zadanie4;

public class Payer {
    private static int NOT_POSITIVE_PAYMENTS = -1;
    private static int NOT_ENOUGH_MONEY = -2;

    public static int payByWallet(Wallet wallet, int price) {
        try {
            wallet.pay(price);
            return wallet.getCache();

        } catch (NotPositivePaymentException e){

            return NOT_POSITIVE_PAYMENTS;
        }
        catch (NotEnoughtMoneyException e) {
            return NOT_ENOUGH_MONEY;
        }
    }
}


