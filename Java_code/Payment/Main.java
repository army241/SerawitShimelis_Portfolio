class Payment {

    public void processPayment(double amount) {
        System.out.println("Processing payment of " + amount);
    }

    public void processPayment(double amount, String currency) {
        System.out.println("Processing payment of " + amount + " " + currency);
    }

    public void processPayment(double amount, String currency, String paymentMethod) {
        System.out.println("Processing " + amount + " " + currency + " via " + paymentMethod);
    }
}

class CreditCardPayment extends Payment {

    @Override
    public void processPayment(double amount, String currency, String paymentMethod) {
        double fee = amount * 0.02;
        double total = amount + fee;

        System.out.println("Credit Card Payment");
        System.out.println("Amount: " + amount + " " + currency);
        System.out.println("Fee: " + fee);
        System.out.println("Total charged: " + total);
    }
}

class PayPalPayment extends Payment {

    @Override
    public void processPayment(double amount, String currency, String paymentMethod) {
        double fee = amount * 0.03;
        double total = amount + fee;

        System.out.println("PayPal Payment");
        System.out.println("Amount: " + amount + " " + currency);
        System.out.println("Fee: " + fee);
        System.out.println("Total charged: " + total);
    }
}

class BankTransferPayment extends Payment {

    @Override
    public void processPayment(double amount, String currency, String paymentMethod) {
        System.out.println("Bank Transfer Payment");
        System.out.println("Amount: " + amount + " " + currency);
        System.out.println("No transaction fee for bank transfers.");
    }
}

public class Main {
    public static void main(String[] args) {

        Payment base = new Payment();

        System.out.println("---- Method Overloading ----");
        base.processPayment(100);
        base.processPayment(200, "USD");
        base.processPayment(300, "USD", "Generic");

        System.out.println("\n---- Method Overriding ----");

        Payment p1 = new CreditCardPayment();
        Payment p2 = new PayPalPayment();
        Payment p3 = new BankTransferPayment();

        p1.processPayment(500, "USD", "Credit Card");
        p2.processPayment(600, "USD", "PayPal");
        p3.processPayment(700, "USD", "Bank Transfer");
    }
} 