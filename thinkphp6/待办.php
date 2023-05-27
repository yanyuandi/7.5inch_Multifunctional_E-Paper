<?php
namespace app\controller;

use app\BaseController;

class Api extends Base
{


    public function index()
    {
        $servername = "你的数据库地址";  
        $username = "root";         
        $password = "数据库密码";  
        $dbname = "todo"; 
        $data = array();

        // 创建连接  
        $conn =mysqli_connect($servername, $username, $password, $dbname);  
         
        // 检测连接  
        $sql = "SELECT * FROM daiban";
        $result = $conn->query($sql);

        if($result) {
            //echo "查询成功";
            $key = 0;
            while ($row = mysqli_fetch_array($result,MYSQLI_ASSOC)) {
                // $user = new User();
                // $user->id = $row["id"];
                // $user->user = $row["user"];
                // $user->comment = $row["comment"];
                // $user->addtime = $row["addtime"];                
                // $data[]=$user;
                $data[$key] = $row;
                $key++;
            }
        }
        return $this->api($data,'获取成功');
    }

}
