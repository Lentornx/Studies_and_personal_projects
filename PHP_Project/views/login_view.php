<?php include_once "../views/includes/static_view_up.php"; ?>
<div id = "content">
            <h2> Login </h2>
            <?php 
                foreach($login["error"] as $msg) 
                    echo $msg."<br>";
            ?>
            <div>
                <form method = "post"  name = "registerForm" >
                    <label for = "login"> login: </label><br>
                    <input type = "text" name = "login" value = "<?php echo $login['login']; ?>" placeholder = "login.."><br>
                    <label for = "password"> password: </label><br>
                    <input type = "password"  value = "<?php echo $login['password']; ?>" name = "password"><br>
                    <input type = "submit" value="login">
                </form>
            </div>
</div>
<?php include_once "../views/includes/static_view_down.php"; ?>