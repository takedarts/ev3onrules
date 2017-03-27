#!/usr/bin/perl

$BASEDIR = $0;
$BASEDIR =~ s/[\/\\]?[^\/\\]+$//;
require "$BASEDIR/functions.pl";

$NAME = 'Rule';
$PATH = 'rule';

sub input {
  do {
    $input = <>;
    $input =~ s/^\s+//;
    $input =~ s/\s+$//;
  } while($input eq '');

  return $input;
}

sub run {
  my $tempdir = $ARGV[0];
  my $srcdir = $ARGV[1];
  my $ruledir = "$srcdir/$PATH";

  # read input
  $| = 1;
  print "rule name (ex: Sample) : ";
  $rule_name = input() . $NAME;
  print "rule number (ex: 0) : ";
  $rule_number = input();
  $| = 0;

  $rule_number = int($rule_number);

  # check files
  $header = "$ruledir/$rule_name.h";
  $source = "$ruledir/$rule_name.cpp";

  if(-e $header){
    die "file already exists: $header";
  }

  if(-e $source){
    die "file already exists: $source";
  }

  # convert
  %map = (
    'RULE_NAME' => $rule_name,
    'RULE_NUMBER' => $rule_number,
  );

  template("$tempdir/$NAME.h.temp", $header, \%map);
  template("$tempdir/$NAME.cpp.temp", $source, \%map);
}

run();

1;
