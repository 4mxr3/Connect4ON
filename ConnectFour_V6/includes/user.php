<?php

class User {

    private $id;
    private $username;
    private $password;
    private $fname;
    private $lname;
    private $wins;
    private $losses;
    private $ties;
    private $admin;

    public function getID() {
        return $this->id;
    }
    public function setID($id){
        $this->id = $id;
    }
    
    public function getUser(){
        return $this->username;
    }
    public function setUser($u){
        $this->username = $u;
    }
    
    public function getPass(){
        return $this->password;
    }
    public function setPass($p){
        $this->password = $p;
    }
    
    public function getfName(){
        return $this->fname;
    }
    public function setfName($fn){
        $this->fname = $fn;
    }
    
    public function getlName(){
        return $this->lname;
    }
    public function setlName($ln){
        $this->lname = $ln;
    }
    
    public function getWins(){
        return $this->wins;
    }
    public function setWins($w){
        $this->wins = $w;
    }
    
    public function getLosses(){
        return $this->losses;
    }
    public function setLosses($l){
        $this->losses = $l;
    }
    
    public function getTies(){
        return $this->ties;
    }
    public function setTies($t){
        $this->ties = $t;
    }
    
    public function getAdmin(){
        return $this->admin;
    }
    public function setAdmin($a){
        $this->admin = $a;
    }
    
    public function printStats(){
        echo $this->fname . " " . $this->lname . "'s Stats <br>";
        echo "Wins-Losses-Ties: ";
        echo $this->wins ."-" . $this->losses . "-" . $this->ties;
    }

    public function fillFromSql($u, $p) {
        require ('./dbconnect.php');

        $query = "SELECT * FROM `entity_user` WHERE `username` = :u AND `password` = :p";

        $statement = $pdo->prepare($query);
        $statement->bindParam(":u", $u);
        $statement->bindParam(":p", $p);
        $statement->execute();
        //Load data from query into array
        $results = $statement->fetchAll(PDO::FETCH_ASSOC);

        //If there is no user with that username and pass, return -1
        if (count($results) == 0) {
            return -1;
        }

        $this->id = $results[0]["id_user"];
        $this->username = $results[0]["username"];
        $this->password = $results[0]["password"];
        $this->fname = $results[0]["first_name"];
        $this->lname = $results[0]["last_name"];
        $this->wins = $results[0]["wins"];
        $this->losses = $results[0]["losses"];
        $this->ties = $results[0]["ties"];
        $this->admin = $results[0]["admin"];
    }

    public function addToSql() {
        //Connect to database
        require ('./dbconnect.php');
        //First see if username is taken
        $query = "SELECT * FROM `entity_user` WHERE `username` = :u";

        $statement = $pdo->prepare($query);
        $statement->bindParam(":u", $this->username);
        
        $statement->execute();
        //Load data from query into array
        $results = $statement->fetchAll(PDO::FETCH_ASSOC);
        
        //If there are any users with that username, return -1
        if (count($results) != 0) {
            return -1;
        }
        
        $query = "INSERT INTO `entity_user`(`username`, `password`, `first_name`, `last_name`, `wins`, `losses`, `ties`) VALUES (:u,:p,:fn,:ln,'0','0','0')";

        $statement = $pdo->prepare($query);
        $statement->bindParam(":u", $this->username);
        $statement->bindParam(":p", $this->password);
        $statement->bindParam(":fn", $this->fname);
        $statement->bindParam(":ln", $this->lname);

        $statement->execute();
    }
}
