#!/usr/bin/perl
#
# ビルドのためのファイルを作成するスクリプト
# usage: perl config.pl SRC_DIR OBJ_DIR RES_DIR EV3RT_DIR APPL_COBJS APPL_CXXOBJS
#   SRC_DIR: ソースコードがあるディレクトリ
#   OBJ_DIR: 作業ディレクトリ
#   RES_DIR: 設定ファイル(app.cfg)が置いてあるディレクトリ
#   EV3RT_DIR: EV3RT(hrp2)のルートディレクトリ
#   APPL_COBJS: 生成するオブジェクトファイル(C)
#   APPL_CXXOBJS:  生成するオブジェクトファイル(C++)
#

sub make_makefile_inc {
  my ($src, $dst, $src_dir, $c_objs, $cpp_objs) = @_;
  my $in, $out;
  my @c_objs = @$c_objs;
  my @cpp_objs = @$cpp_objs;
  my $c_objs_str = join(' ', @c_objs);
  my $cpp_objs_str = join(' ', @cpp_objs);
  
  if(!open($in, $src)){
    die "can't open file: $src";
  }
  
  if(!open($out, ">$dst")){
    die "can't open file: $dst";
  }
  
  while(<$in>){
    print $out $_;
  }
  
  print $out "# ----- added by config.pl -----\r\n";
  print $out "MOD_SRCDIR := $src_dir\r\n";
  print $out "MOD_COBJS := $c_objs_str\r\n";
  print $out "MOD_CXXOBJS := $cpp_objs_str\r\n";

  close($in);
  close($out);
}

sub make_makefile_app {
  my ($src, $dst, $src_dir, $ev3rt_dir) = @_;
  my $in, $out;

  if(!open($in, $src)){
    die "can't open file: $src";
  }
  
  if(!open($out, ">$dst")){
    die "can't open file: $dst";
  }
  
  while(<$in>){
    ~s/KERNELDIR = \@\(SRCDIR\)/KERNELDIR = ${ev3rt_dir}/;
    ~s/APPLDIR   = \@\(APPLDIR\)/APPLDIR   = ${src_dir}/;
    ~s/include ..\/common\/Makefile.prj.common/include Makefile.prj/;
    ~s/COPTS \+= \@\(COPTS\)/COPTS += -DBUILD_MODULE/;
    ~s/INCLUDES \+= -I\@\(APPLDIR\)/INCLUDES += -I${src_dir}/;
    ~s/-I\@\(APPLDIR\)\/..\/common/-I${ev3rt_dir}\/sdk\/common/;
    ~s/MODCFG = \@\(APPLDIR\)\/app.cfg/MODCFG = app.cfg/;
    ~s/include \@\(APPLDIR\)\/Makefile.inc/include Makefile.inc/;
    ~s/APPL_CXXOBJS \+= app.o \@\(APPLOBJS\)/APPL_CXXOBJS \+=/;
    ~s/MODOBJS \+= app.o \@\(APPLOBJS\)/MODOBJS \+=/;
    ~s/include \$\(LOADERDIR\)\/app\/Makefile.lum/include Makefile.lum/;
    print $out $_;
  }
  
  close($in);
  close($out);
}

sub make_makefile_lum {
  my ($src, $dst, $tmp) = @_;
  my $in, $out, $add;

  if(!open($in, $src)){
    die "can't open file: $src";
  }
  
  if(!open($add, "$tmp")){
    die "can't open file: $tmp";
  }
  
  if(!open($out, ">$dst")){
    die "can't open file: $dst";
  }
  
  while(<$in>){
    ~s/(\$\(OBJFILE\): \$\(\CFG_OUT_SRCS\) \$\(ALL_OBJS\) \$\(ALL_CXXOBJS\))/$1 \$\(MOD_COBJS\) \$\(MOD_CXXOBJS\)/; 
    ~s/(\@\$\(LINK\) \$\(LDFLAGS\) -o \$\(OBJFILE\) \$\(ALL_OBJS\) \$\(ALL_CXXOBJS\))/$1 \$\(MOD_COBJS\) \$\(MOD_CXXOBJS\)/; 
    print $out $_;
  }
  
  while(<$add>){
    print $out $_;
  }
  
  close($in);
  close($add);
  close($out);
}

sub make_makefile_prj {
  my ($src, $dst, $ev3rt_dir) = @_;
  my $in, $out;

  if(!open($in, $src)){
    die "can't open file: $src";
  }
  
  if(!open($out, ">$dst")){
    die "can't open file: $dst";
  }
  
  while(<$in>){
    ~s/EV3RT_SDK_COM_DIR := \$\(.+\)/EV3RT_SDK_COM_DIR := ${ev3rt_dir}\/sdk\/common/g;
    ~s/EV3RT_SDK_API_DIR := \$\(.+\)/EV3RT_SDK_API_DIR := ${ev3rt_dir}\/sdk\/common\/ev3api/;
    ~s/EV3RT_SDK_LIB_DIR := \$\(.+\)/EV3RT_SDK_LIB_DIR := ${ev3rt_dir}\/sdk\/common\/library/;
    ~s/(INCLUDES \+= \$\(foreach)/# $1/;
    ~s/(APPL_DIR \+= \$\(foreach)/# $1/;
    print $out $_;
  }
  
  close($in);
  close($out);
}

sub make_cfgfile {
  my ($src, $dst, $c_objs, $cpp_objs) = @_;
  my $in, $out;
  my @c_objs = @$c_objs;
  my @cpp_objs = @$cpp_objs;
  
  if(!open($in, $src)){
    die "can't open file: $src";
  }
  
  if(!open($out, ">$dst")){
    die "can't open file: $dst";
  }
  
  while(<$in>){
    print $out $_;
  }
  
  print $out "\r\n/* ----- added by config.pl ----- */\r\n";
  
  foreach(@c_objs){
    print $out "ATT_MOD(\"$_\");\r\n";
  }
  
  foreach(@cpp_objs){
    print $out "ATT_MOD(\"$_\");\r\n";
  }

  close($in);
  close($out);
}


sub run {
  my $src_dir = $ARGV[0];
  my $obj_dir = $ARGV[1];
  my $res_dir = $ARGV[2];
  my $ev3rt_dir = $ARGV[3];
  my $c_objs = $ARGV[4];
  my $cpp_objs = $ARGV[5];

  my @c_objs = grep $_ ne '', split(/\s+/, $c_objs);
  my @cpp_objs = grep $_ ne '', split(/\s+/, $cpp_objs);
  
  my $makefile_inc_src = "${res_dir}/Makefile.inc";
  my $makefile_inc_dst = "${obj_dir}/Makefile.inc";
  my $makefile_app_src = "${ev3rt_dir}/sdk/common/Makefile.app";
  my $makefile_app_dst = "${obj_dir}/Makefile.app";
  my $makefile_lum_src = "${ev3rt_dir}/target/ev3_gcc/dmloader/app/Makefile.lum";
  my $makefile_lum_dst = "${obj_dir}/Makefile.lum";
  my $makefile_lum_tmp = "${res_dir}/Makefile.lum";
  my $makefile_prj_src = "${ev3rt_dir}/sdk/common/Makefile.prj.common";
  my $makefile_prj_dst = "${obj_dir}/Makefile.prj";
  my $cfgfile_src = "${res_dir}/app.cfg";
  my $cfgfile_dst = "${obj_dir}/app.cfg";
  
  make_makefile_inc($makefile_inc_src, $makefile_inc_dst, $src_dir, \@c_objs, \@cpp_objs);
  make_makefile_app($makefile_app_src, $makefile_app_dst, $src_dir, $ev3rt_dir);
  make_makefile_lum($makefile_lum_src, $makefile_lum_dst, $makefile_lum_tmp);
  make_makefile_prj($makefile_prj_src, $makefile_prj_dst, $ev3rt_dir);
  make_cfgfile($cfgfile_src, $cfgfile_dst, \@c_objs, \@cpp_objs);
}

run();

1;
