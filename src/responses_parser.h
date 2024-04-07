#ifndef RESPONSES_PARSER
#define RESPONSES_PARSER

enum ResponseCode {
    ServiceReady = 220,
    ServiceClosing = 221,
    ActionCompleted = 250,
    StartMessageInpuit = 354,
    ServiceNotAvailable = 421,
    UserMailboxUnavailableTryLater = 450,
    ServerError = 451,
    ServerStorageIfFull = 452,
    CannotHandleCommandTryLater = 455,
    UnknownCommand = 500,
    IncorrectCommandSyntax = 501,
    CommandNotImplemented = 502,
    BadCommandsSequence = 503,
    CommandParamNotImplemented = 504,
    DummyServerResponse = 521,
    SupressedBySpamFilter = 451,
    UserMailboxUnavailable = 550,
    RecipientIsNotLocalToServer = 551,
    ExceedStorageAllocation = 552,
    InvalidMailboxName = 553,
    MailboxIsDisabled = 554
};


#endif