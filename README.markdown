# CedarCPP

BDD-style testing framework created from [cedar](https://github.com/pivotal/cedar).

This library is under heavy development and is currently in a pre alpha state. It is by no means stable at this point.


## Usage


### Clone from GitHub


### Installation


## Matchers

Cedar has a new set of matchers that use C++ templates to circumvent type issues
that plague other matcher libraries. CedarCPP uses these same matchers.

    expect(aString).to(equal("something"));
    expect(anInteger).to(equal(7));
    expect(anInteger).to_not(equal(9));
    expect(aBoolean).to(equal(true));

although you would more likely write the last line as:

    expect(aBoolean).to(be_truthy());

Here is a list of built-in matchers you can use:

    expect(...).to(be_nil());

    expect(...).to(be_truthy());
    expect(...).to_not(be_truthy());

    expect(...).to(equal(10));
    expect(...).to == 10; // shortcut to the above
    expect(...) == 10; // shortcut to the above

    expect(...).to(be_greater_than(5));
    expect(...).to > 5; // shortcut to the above
    expect(...) > 5; // shortcut to the above

    expect(...).to(be_greater_than_or_equal_to(10));
    expect(...).to(be_gte(10)); // shortcut to the above
    expect(...).to >= 10; // shortcut to the above
    expect(...) >= 10; // shortcut to the above

    expect(...).to(be_less_than(11));
    expect(...).to < 11; // shortcut to the above
    expect(...) < 11; // shortcut to the above

    expect(...).to(be_less_than_or_equal_to(10));
    expect(...).to(be_lte(10)); //shortcut to the above
    expect(...).to <= 10; // shortcut to the above
    expect(...) <= 10; // shortcut to the above

    expect(...).to(be_close_to(5)); // default within(.01)
    expect(...).to(be_close_to(5).within(.02));

    expect(...).to(be_instance_of([NSObject class]));
    expect(...).to(be_instance_of([NSObject class]).or_any_subclass());

    expect(...).to(be_same_instance_as(object));

    expect(...).to(contain("something"));
    expect(...).to(be_empty());

These matchers use C++ templates for type deduction.  You'll need to do two things to use them:

* Add the following line to the top of your spec files, after the file includes:

        using namespace Cedar::Matchers;

It's also theoretically very easy to add your own matchers without modifying the
CedarCPP library (more on this later).


Note: If you prefer RSpec's `should` syntax you can write your expectations as follows:

    1 + 2 should equal(3);
    glass should_not be_empty();

## Mocks and stubs
  CedarCPP's internal tests use mockitopp. CedarCPP itself has no built in support for these.

## Contributions and feedback

Welcomed!  Feel free to fork and send pull requests.

[Cedar] (http://github.com/pivotal/cedar/) Copyright (c) 2012 Pivotal Labs. This software is licensed under the MIT License.
