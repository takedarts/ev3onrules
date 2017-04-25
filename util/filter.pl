#!/usr/bin/perl

$BASEDIR = $0;
$BASEDIR =~ s/[\/\\]?[^\/\\]+$//;
require "$BASEDIR/functions.pl";

$NAME = 'Filter';
$PATH = 'filter';

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
  my $filterdir = "$srcdir/$PATH";

  # read input
  $| = 1;
  print "filter name (e.g. Sample) : ";
  $filter_name = input() . $NAME;
  print "filter number (e.g. 0) : ";
  $filter_number = input();
  $| = 0;

  $filter_number = int($filter_number);

  # check files
  $header = "$filterdir/$filter_name.h";
  $source = "$filterdir/$filter_name.cpp";

  if(-e $header){
    die "file already exists: $header";
  }

  if(-e $source){
    die "file already exists: $source";
  }

  # convert
  %map = (
    'FILTER_NAME' => $filter_name,
    'FILTER_NUMBER' => $filter_number,
  );

  template("$tempdir/$NAME.h.temp", $header, \%map);
  template("$tempdir/$NAME.cpp.temp", $source, \%map);
}

run();

1;
