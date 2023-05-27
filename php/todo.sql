-- phpMyAdmin SQL Dump
-- version 4.8.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: 2023-05-26 14:23:43
-- 服务器版本： 5.5.60-log
-- PHP Version: 7.4.33

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `todo`
--

-- --------------------------------------------------------

--
-- 表的结构 `daiban`
--

CREATE TABLE `daiban` (
  `id` int(11) NOT NULL,
  `thing` varchar(200) NOT NULL,
  `isdone` varchar(200) NOT NULL,
  `isimp` varchar(200) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;

--
-- 转存表中的数据 `daiban`
--

INSERT INTO `daiban` (`id`, `thing`, `isdone`, `isimp`) VALUES
(3, 'BOSS直聘上投简历', '0', '1'),
(130, '设计开机画面', '', ''),
(131, '设计配网界面', '', ''),
(129, '增加温湿度显示', '', '0'),
(128, '写每个区域更新代码', '1', '0'),
(127, '设置自动更新间隔', '1', ''),
(126, '三个按钮设置功能', '1', ''),
(125, '增加电量显示', '1', '');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `daiban`
--
ALTER TABLE `daiban`
  ADD PRIMARY KEY (`id`);

--
-- 在导出的表使用AUTO_INCREMENT
--

--
-- 使用表AUTO_INCREMENT `daiban`
--
ALTER TABLE `daiban`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=148;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
