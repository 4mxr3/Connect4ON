<?php
session_start();
$_SESSION["loggedIn"] = false;
?>

<?php
include("./includes/header.php");
?>

<div id="login">
    <form method="post" action="./registerhandler.php" onsubmit="return validateRegisterForm()">
        <label for="user">Username:</label>
        <input type="text" name="user" id="user">
        <br>
        <label for="pass">Password:</label>
        <input type="text" name="pass" id="pass">
        <br>
        <label for="fname">First Name:</label>
        <input type="text" name="fname" id="fname">
        <br>
        <label for="lname">Last Name:</label>
        <input type="text" name="lname" id="lname">
        <br>
        <label for="admin">Admin:</label>
        Yes<input type="radio" name="admin" value="1">
        No<input type="radio" name="admin" value="0" checked>
        <br> <br>
        <input type="submit" value="Register">
        <br> <br>
    </form>
</div>

<div id="response">
    <?php
    echo $_SESSION["err"];
    $_SESSION["err"] = "";
    ?>
</div>

<script>
function validateRegisterForm() {
    var user = document.getElementById("user").value;
    var pass = document.getElementById("pass").value;
    var fname = document.getElementById("fname").value;
    var lname = document.getElementById("lname").value;

    if (user === "" || pass === "" || fname === "" || lname === "") {
        alert("All fields must be filled out");
        return false;
    }

    if (pass.length < 5) {
        alert("Password must be at least 5 characters long");
        return false;
    }

    return true;
}
</script>

<?php
include("./includes/footer.html");
?>
