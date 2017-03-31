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
use File::Spec;

sub make_makefile_inc {
  my ($src, $dst, $src_dir, $obj_dir, $c_objs, $cpp_objs) = @_;
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

  $src_dir = File::Spec->abs2rel($src_dir, $obj_dir);

  print $out "# ----- added by config.pl -----\r\n";
  print $out "MOD_SRCDIR := $src_dir\r\n";
  print $out "MOD_COBJS := $c_objs_str\r\n";
  print $out "MOD_CXXOBJS := $cpp_objs_str\r\n";

  close($in);
  close($out);
}

sub make_makefile_app {
  my ($src, $dst, $src_dir, $obj_dir, $ev3rt_dir) = @_;
  my $in, $out;

  if(!open($in, $src)){
    die "can't open file: $src";
  }

  if(!open($out, ">$dst")){
    die "can't open file: $dst";
  }

  $src_dir = File::Spec->abs2rel($src_dir, $obj_dir);
  $ev3rt_dir = File::Spec->abs2rel($ev3rt_dir, $obj_dir);

  while(<$in>){
    ~s/\@\(SRC_DIR\)/${src_dir}/;
    ~s/\@\(EV3RT_DIR\)/${ev3rt_dir}/;
    print $out $_;
  }

  close($in);
  close($out);
}

sub make_makefile_lum {
  my ($src, $dst) = @_;
  my $in, $out, $add;

  if(!open($in, $src)){
    die "can't open file: $src";
  }

  if(!open($out, ">$dst")){
    die "can't open file: $dst";
  }

  while(<$in>){
    print $out $_;
  }

  close($in);
  close($out);
}

sub make_makefile_prj {
  my ($src, $dst, $obj_dir, $ev3rt_dir) = @_;
  my $in, $out;

  if(!open($in, $src)){
    die "can't open file: $src";
  }

  if(!open($out, ">$dst")){
    die "can't open file: $dst";
  }

  $ev3rt_dir = File::Spec->abs2rel($ev3rt_dir, $obj_dir);

  while(<$in>){
    ~s/\@\(EV3RT_DIR\)/${ev3rt_dir}/;
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
  my $makefile_app_src = "${res_dir}/Makefile.app";
  my $makefile_app_dst = "${obj_dir}/Makefile.app";
  my $makefile_lum_src = "${res_dir}/Makefile.lum";
  my $makefile_lum_dst = "${obj_dir}/Makefile.lum";
  my $makefile_prj_src = "${res_dir}/Makefile.prj";
  my $makefile_prj_dst = "${obj_dir}/Makefile.prj";
  my $cfgfile_src = "${res_dir}/app.cfg";
  my $cfgfile_dst = "${obj_dir}/app.cfg";

  make_makefile_inc($makefile_inc_src, $makefile_inc_dst, $src_dir, $obj_dir, \@c_objs, \@cpp_objs);
  make_makefile_app($makefile_app_src, $makefile_app_dst, $src_dir, $obj_dir, $ev3rt_dir);
  make_makefile_lum($makefile_lum_src, $makefile_lum_dst);
  make_makefile_prj($makefile_prj_src, $makefile_prj_dst, $obj_dir, $ev3rt_dir);
  make_cfgfile($cfgfile_src, $cfgfile_dst, \@c_objs, \@cpp_objs);
}

run();

1;
