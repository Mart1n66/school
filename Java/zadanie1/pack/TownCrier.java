package pack;

public class TownCrier {
    private String lastMessage;
    private int numberOfLastMessageAnnounced;

    public TownCrier(){
        this.numberOfLastMessageAnnounced = 0;
    }

    public void setMessage(String message){
        this.lastMessage = message;
        this.numberOfLastMessageAnnounced = 0;
    }

    public String announce(){
        this.numberOfLastMessageAnnounced ++;
        return lastMessage;
    }

    public int getNumberOfLastMessageAnnounced(){
        return this.numberOfLastMessageAnnounced;
    }
}
