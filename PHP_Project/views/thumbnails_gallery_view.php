<?php include_once "../views/includes/static_view_up.php"; ?>
        <div id = "content">
            <?php
            if(!isset($gallery['logged_in_user_login']) || ($gallery['logged_in_user_login'] === null))
                {
                    echo '<a href = "register"> <button>register</button> </a>';
                    echo '<a href = "login"> <button>log in</button> </a>';
                }
                else
                {
                    echo '<a href = "logout"> <button>log out</button> </a>';

                    echo '<span> <strong>hello '.$gallery['logged_in_user_login'] .'!</strong></span>';
                }                   
                echo '<a href = "fav_thumbnails_gallery"> <button> view favourites </button> </a>';
            ?>  

            <div class = "center">
                <?php  
                   echo isset($gallery["message"]) ?  $gallery["message"]."<br>"  : null;
                ?>
                <h2> Gallery </h2> 
                <a href = "upload"> <button>click here to add a picture</button> </a> 
                <h3> click a picture to zoom in </h3>
                    <?php 
                        //print_r($thumbnails_gallery);
                        $count = 0;
                        if(isset($thumbnails_gallery))
                        {
                            echo "<form name = 'favouritesForm' method = 'POST'>";
                            foreach($thumbnails_gallery as $thumbnail){
                                if($_SESSION['in_favourites'][$thumbnail['file_name']] == true)
                                    $checked = "checked";
                                else $checked = "";
                                echo  "<table style = 'display:inline;'>
                                            <tr><td> title:".$thumbnail["title"]." </td></tr>
                                            <tr><td> author:".$thumbnail["author"]."</td></tr>
                                            <tr><td><a target = 'blank' href = '".PHOTOS_WATERMARK_PATH."/".$thumbnail["file_name"]."'><img class='small_img' src='".THUMBNAILS_PATH."/".$thumbnail["file_name"]."'></a></td></tr>
                                            <tr><td><input type = 'checkbox' name = 'favourite_thumbnails[]' value = ".$thumbnail["file_name"]. " " . $checked . ">
                                       </table>";
                            }
                            echo "<br><input type = 'submit' value = 'save your favourites on this page'>
                                  </form>";
                        }
                    ?>        
                <div id = "scrollBar">
                    <br> 
                    <?php 
                        for($i = 1; $i <= $gallery["scrollbar_count"]; $i++)
                        {
                            
                            if($i == $gallery["page_id"])
                               { $class = "class = active";}
                            else
                                $class = "";
                            echo "<a ".$class." href = 'thumbnails_subgallery&id=".$i."'> |".$i."| </a>";
                        }  
                    ?>
                </div>
            </div>
        </div>
<?php include_once "../views/includes/static_view_down.php"; ?>
