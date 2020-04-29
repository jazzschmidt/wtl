# wtl - when to leave
Tells when to leave work.

## Synposis
```lang-bash
wtl [-c <config>] [<time=HH:MM>]
wtl -h <hours> [<time=HH:MM>]
```

## Options
When invoked without arguments, `wtl` tries to load the default configuration
from the home directory and sets `<time>` to the current time if not already
configured for today.

- `-c <config>`: Uses the working hours configuration `<config>`,
  defaults to `~/.wtl`
- `-h`: Defines how many hours should be added to `<time>`

## Configuration
The configuration file is used to set working hours for different days of the
week. There must be only one `key=value` per line. Consecutive configurations
overwrite previous ones.

The following configuration keys are available:
- all days: `**`
- all working days (mon - fri): `*`
- individual days: `sun`, `mon`, `tue`, `wed`, `thu`, `fri`, and `sat`

Furthermore, the following keys will be written by `wtl` and should not be
manually set:
- initial starting time: `started`
- day of the week: `wday`

**Example Configuration**

Suppose, you need to work *37.5 hrs per week*, take a *50 min lunch break*
and want to spend less time at the office on fridays, you could use something
like this:

```
*=8:50
fri=6:20
```

## Examples
**Using with default configuration**
```lang-bash
$ date "+%H:%M"
08:27

$ wtl # Use the current time
You need to work until 17:17
Started: 08:27

$ # ...

$ date "+%H:%M"
11:53
$ wtl # Any subsequent calls use the configured time
You need to work until 17:17
Started: 08:27
```

**Explicit hours configuration**
```lang-bash
$ wtl -h 8:50 09:00 | grep until | cut -d" " -f6 # 8:50 hrs working time
17:50
```

**Custom configuration file**
```lang-bash
$ date "+%H:%M"
08:11

$ wtl -c ./my-working-hours
You need to work until 14:41
Started: 08:11
```
