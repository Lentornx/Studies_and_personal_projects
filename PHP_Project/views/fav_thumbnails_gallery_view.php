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
            ?>  
            
            <div class = "center">
                <?php  
                   echo isset($gallery["message"]) ? $gallery["message"]."<br>"  : null;
                ?>
                <h2> Favourites </h2> 
                <h3> click a picture to zoom in </h3>
                    <?php 
                        $count = 0;
                        if(isset($fav_thumbnails_gallery))
                        {
                            echo "<form name = 'deleted_from_fav' method = 'POST'>";
                            foreach($fav_thumbnails_gallery as $thumbnail){
                                echo  "<table style = 'display:inline;'>
                                            <tr><td> title:".$thumbnail["title"]." </td></tr>
                                            <tr><td> author:".$thumbnail["author"]."</td></tr>
                                            <tr><td><a target = 'blank' href = '".PHOTOS_WATERMARK_PATH."/".$thumbnail["file_name"]."'><img class='small_img' src='".THUMBNAILS_PATH."/".$thumbnail["file_name"]."'></a></td></tr>
                                            <tr><td><input type = 'checkbox' name = 'deleted_from_fav[]' value = ".$thumbnail["file_name"]. ">
                                       </table>";
                            }
                            echo "<br><input type = 'submit' value = 'delete from favourites'>
                                  </deleted_from_fav>";
                        }
                    ?>        
                <div id = "scrollBar">
                    <br> 
                    <?php 
                        for($i = 1; $i <= $gallery["fav_scrollbar_count"]; $i++)
                        {
                            
                            if($i == $gallery["fav_page_id"])
                                $class = "class = active";
                            else
                                $class = "";
                            echo "<a ".$class." href = 'fav_thumbnails_subgallery&id=".$i."'> |".$i."| </a>";
                        }  
                    ?>
                </div>
            </div>
        </div>
<?php include_once "../views/includes/static_view_down.php"; ?>
