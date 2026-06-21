package oop.zadanie2;

public class DayWeb extends AbstractWeb {
    private static final String[] days = {"pondelok", "utorok", "streda", "stvrtok", "piatok", "sobota", "nedela"};

    public DayWeb(User[] users){
        super(users);
    }

    @Override
    public Response getById(Request request){
        if(!authenticate(request)){
            return new Response(false, "");
        }

        int id = request.getId();
        if(id < 1 || id > 7){
            return new Response(false, "");
        }

        return new Response(true, days[id - 1]);
    }

    @Override
    public Response getAll(Request request){
        if(!authenticate(request)){
            return new Response(false, "");
        }

        String joinedDays = String.join(", ", days);
        return new Response(true, joinedDays);
    }
}
