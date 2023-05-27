<?php
namespace app\controller;

use app\BaseController;
use think\Request;


class Weather extends BaseController
{
    public function index(int $id = 101010100)
    {
        $url = "https://devapi.qweather.com/v7/weather/now?location=". $id ."&key=这里替换你的秘钥&gzip=n";
        $data = $this->get_request($url);
        // 数据返回
        return $data;
    }
    function post_request($url, $data = null)
    {
        $curl = curl_init();
        curl_setopt($curl, CURLOPT_URL, $url);
        curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, FALSE);
        curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, FALSE);
        curl_setopt($curl, CURLOPT_POST, 1);
        curl_setopt($curl, CURLOPT_POSTFIELDS, $data);
        curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
        curl_setopt($curl, CURLOPT_ENCODING, "gzip"); // 添加此行以支持 gzip 解压缩
        $output = curl_exec($curl);
        curl_close($curl);
        return $output;
    }
    function get_request($url)
    {
        $curl = curl_init();
        curl_setopt($curl, CURLOPT_URL, $url);
        curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, FALSE);
        curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, FALSE);
        curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
        curl_setopt($curl, CURLOPT_ENCODING, "gzip"); // 添加此行以支持 gzip 解压缩
        $output = curl_exec($curl);
        curl_close($curl);
        return $output;
    }
}
