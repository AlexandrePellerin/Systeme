/*************DRIVER ODBC(WINDOWS)****************/
// enregistrement du driver
Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
// connexion à la base
String url = "jdbc:odbc:BDDsrc"; // remplacer le BDDsrc par le nom choisi dans odbc
String nom = "admin"; // son nom
String mdp = "xxx"; // son mdp
Connection con = DriverManager.getConnection(url, nom, mdp);

/************DRIVER POSGRE***********************/ //ne pas oublier le .jar
// enregistrement du driver
Class.forName("org.postgresql.Driver");
// connexion a la base
String url = "jdbc:postgresql://psqlserv/n3p1";
String nom = "verquinc"; // son nom
String mdp = "moi"; // son mdp
Connection con = DriverManager.getConnection(url, nom, mdp);

/************Requette***************************/
Statement stmt = con.createStatement(); //objet pour la requette
stmt.executeUpdate("String sql"); // permet de faire des UPDATE, DELETE, INSERT, CREATE, DROP
ResultSet resQ = stmt.executeQuery("String sql"); // permet de faire un SELECT

/************Servlet***************************/
//fichier de base 
@WebServlet("/servlet/nom de la servlet") //remplacer le nom de la servlet
public class "nom de la class" extends HttpServlet { //remlacer le nom de la class
    public void service(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
	PrintWriter out = res.getWriter();
	res.setContentType("text/html");

	out.println("<!DOCTYPE html");
	out.println("<html>");
	out.println("<head><title>Select</title>"); //remplacer le titre
	out.println("<meta charset=\"utf-8\">");
	out.println("<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
	out.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
	out.println("<link rel=\"stylesheet\"href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css\">");
	out.println("</head><body><center>");

	// code ...

	out.println("<table class=\"table-centered table-hover table-condensed>");
	out.println("</center> </body>");
	out.println("</html>");
    }
}		
     
/**************truc utile***************************/
req.getParameter("parametre"); // permet de get les parametre dans l'url
res.sendRedirect("servlet"); // permet de rediriger vers une servlet

//faire un formulaire

out.println("<form action=\"nom de la servlet\" method=\"post\">"); // remplacer le nom de la servlet
//text box
out.println("<INPUT TYPE=\"text\" SIZE=\"20\" NAME=\"nom\" VALUE=\"\">"); // remplacer le nom du champ
//champ cacher
out.println("<INPUT TYPE=\"hidden\" NAME=\"nom\" VALUE=\"\">"); // remplacer le nom du champ
//bouton
out.println("<INPUT TYPE=\"submit\">");
out.println("</form>");

//faire un tableau il se fait ligne par ligne et case par case

out.println("<table border=\"1\">");
out.println("<tr>"); //une ligne
out.println("<td> text </td>"); // une case
out.println("</tr>");
out.println("</table>");

/*sql
"select * from table"
"delete from table where condition"
"insert into table values(...,...,...)"
"update table set machin=... truc=.... where condition" // mettre toute les colones apres le set
"drop table table cascade"
"create table nom(machin text, truc int, constraint p_Nom primary key (machin))"

//si c'est du text ne pas oublier ' autour du text 
*/
