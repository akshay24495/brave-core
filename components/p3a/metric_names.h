/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_P3A_METRIC_NAMES_H_
#define BRAVE_COMPONENTS_P3A_METRIC_NAMES_H_

#include <string_view>

#include "base/containers/fixed_flat_set.h"

namespace p3a {

// Allowlist for histograms that we collect.
// A metric must be listed here to be reported.
//
// Please keep them properly sorted within their categories.
//
// Could be replaced with something built dynamically,
// although so far we've found it a useful review point.
//
// TODO(iefremov) Clean up obsolete metrics.
//
// clang-format off
inline constexpr auto kCollectedTypicalHistograms =
  base::MakeFixedFlatSet<std::string_view>(base::sorted_unique,{
    "Brave.AIChat.AcquisitionSource",
    "Brave.AIChat.AvgPromptCount",
    "Brave.AIChat.ChatCount",
    "Brave.AIChat.ContextMenu.FreeUsages",
    "Brave.AIChat.ContextMenu.MostUsedAction",
    "Brave.AIChat.ContextMenu.PremiumUsages",
    "Brave.AIChat.Enabled.2",
    "Brave.AIChat.Enabled.SidebarEnabledA",
    "Brave.AIChat.Enabled.SidebarEnabledB",
    "Brave.AIChat.NewUserReturning",
    "Brave.AIChat.OmniboxOpens",
    "Brave.AIChat.OmniboxWeekCompare",
    "Brave.AIChat.UsageWeekly",
    "Brave.AIChat.UsageWeekly.SidebarEnabledA",
    "Brave.AIChat.UsageWeekly.SidebarEnabledB",
    "Brave.Core.BookmarkCount",
    "Brave.Core.CrashReportsEnabled",
    "Brave.Core.DomainsLoaded",
    "Brave.Core.FailedHTTPSUpgrades.2",
    "Brave.Core.IsDefault",
    "Brave.Core.LastTimeIncognitoUsed",
    "Brave.Core.LocationNewEntries",
    "Brave.Core.NewTabMethods",
    "Brave.Core.NumberOfExtensions",
    "Brave.Core.PagesLoaded.2",
    "Brave.Core.PagesReloaded",
    "Brave.Core.TabCount",
    "Brave.Core.TorEverUsed",
    "Brave.Core.WeeklyUsage",
    "Brave.Core.WindowCount.2",
    "Brave.DNS.AutoSecureRequests",
    "Brave.DNS.AutoSecureRequests.Cloudflare",
    "Brave.DNS.AutoSecureRequests.Quad9",
    "Brave.DNS.AutoSecureRequests.Wikimedia",
    "Brave.DNS.SecureSetting",
    "Brave.Extensions.AdBlock",
    "Brave.IOS.IsLikelyDefault",

    // IPFS
    "Brave.IPFS.DaemonRunTime",
    "Brave.IPFS.DetectionPromptCount",
    "Brave.IPFS.GatewaySetting",
    "Brave.IPFS.IPFSCompanionInstalled",
    "Brave.IPFS.LocalNodeRetention",

    "Brave.Importer.ImporterSource.2",
    "Brave.NTP.CustomizeUsageStatus.2",
    "Brave.NTP.NewTabsCreated.3",
    "Brave.NTP.SponsoredImagesEnabled",
    "Brave.NTP.SponsoredNewTabsCreated.2",
    "Brave.Omnibox.SearchCount.3",

    // P2A
    // Ad Impressions
    "Brave.P2A.ad_notification.impressions",
    "Brave.P2A.ad_notification.impressions_per_segment.architecture",
    "Brave.P2A.ad_notification.impressions_per_segment.artsentertainment",
    "Brave.P2A.ad_notification.impressions_per_segment.automotive",
    "Brave.P2A.ad_notification.impressions_per_segment.business",
    "Brave.P2A.ad_notification.impressions_per_segment.careers",
    "Brave.P2A.ad_notification.impressions_per_segment.cellphones",
    "Brave.P2A.ad_notification.impressions_per_segment.crypto",
    "Brave.P2A.ad_notification.impressions_per_segment.education",
    "Brave.P2A.ad_notification.impressions_per_segment.familyparenting",
    "Brave.P2A.ad_notification.impressions_per_segment.fashion",
    "Brave.P2A.ad_notification.impressions_per_segment.folklore",
    "Brave.P2A.ad_notification.impressions_per_segment.fooddrink",
    "Brave.P2A.ad_notification.impressions_per_segment.gaming",
    "Brave.P2A.ad_notification.impressions_per_segment.healthfitness",
    "Brave.P2A.ad_notification.impressions_per_segment.history",
    "Brave.P2A.ad_notification.impressions_per_segment.hobbiesinterests",
    "Brave.P2A.ad_notification.impressions_per_segment.home",
    "Brave.P2A.ad_notification.impressions_per_segment.law",
    "Brave.P2A.ad_notification.impressions_per_segment.military",
    "Brave.P2A.ad_notification.impressions_per_segment.other",
    "Brave.P2A.ad_notification.impressions_per_segment.personalfinance",
    "Brave.P2A.ad_notification.impressions_per_segment.pets",
    "Brave.P2A.ad_notification.impressions_per_segment.realestate",
    "Brave.P2A.ad_notification.impressions_per_segment.science",
    "Brave.P2A.ad_notification.impressions_per_segment.sports",
    "Brave.P2A.ad_notification.impressions_per_segment.technologycomputing",
    "Brave.P2A.ad_notification.impressions_per_segment.travel",
    "Brave.P2A.ad_notification.impressions_per_segment.untargeted",
    "Brave.P2A.ad_notification.impressions_per_segment.weather",
        // Ad Opportunities
    "Brave.P2A.ad_notification.opportunities",
    "Brave.P2A.ad_notification.opportunities_per_segment.architecture",
    "Brave.P2A.ad_notification.opportunities_per_segment.artsentertainment",
    "Brave.P2A.ad_notification.opportunities_per_segment.automotive",
    "Brave.P2A.ad_notification.opportunities_per_segment.business",
    "Brave.P2A.ad_notification.opportunities_per_segment.careers",
    "Brave.P2A.ad_notification.opportunities_per_segment.cellphones",
    "Brave.P2A.ad_notification.opportunities_per_segment.crypto",
    "Brave.P2A.ad_notification.opportunities_per_segment.education",
    "Brave.P2A.ad_notification.opportunities_per_segment.familyparenting",
    "Brave.P2A.ad_notification.opportunities_per_segment.fashion",
    "Brave.P2A.ad_notification.opportunities_per_segment.folklore",
    "Brave.P2A.ad_notification.opportunities_per_segment.fooddrink",
    "Brave.P2A.ad_notification.opportunities_per_segment.gaming",
    "Brave.P2A.ad_notification.opportunities_per_segment.healthfitness",
    "Brave.P2A.ad_notification.opportunities_per_segment.history",
    "Brave.P2A.ad_notification.opportunities_per_segment.hobbiesinterests",
    "Brave.P2A.ad_notification.opportunities_per_segment.home",
    "Brave.P2A.ad_notification.opportunities_per_segment.law",
    "Brave.P2A.ad_notification.opportunities_per_segment.military",
    "Brave.P2A.ad_notification.opportunities_per_segment.other",
    "Brave.P2A.ad_notification.opportunities_per_segment.personalfinance",
    "Brave.P2A.ad_notification.opportunities_per_segment.pets",
    "Brave.P2A.ad_notification.opportunities_per_segment.realestate",
    "Brave.P2A.ad_notification.opportunities_per_segment.science",
    "Brave.P2A.ad_notification.opportunities_per_segment.sports",
    "Brave.P2A.ad_notification.opportunities_per_segment.technologycomputing",
    "Brave.P2A.ad_notification.opportunities_per_segment.travel",
    "Brave.P2A.ad_notification.opportunities_per_segment.untargeted",
    "Brave.P2A.ad_notification.opportunities_per_segment.weather",
    "Brave.P2A.inline_content_ad.impressions",
    "Brave.P2A.inline_content_ad.opportunities",
    "Brave.P2A.new_tab_page_ad.impressions",
    "Brave.P2A.new_tab_page_ad.opportunities",
    "Brave.P3A.SentAnswersCount",
    "Brave.Playlist.FirstTimeOffset",
    "Brave.Playlist.NewUserReturning",
    "Brave.Playlist.UsageDaysInWeek",
    "Brave.Rewards.AdTypesEnabled",
    "Brave.Rewards.AutoContributionsState.3",
    "Brave.Rewards.CustomNotificationAdPosition",
    "Brave.Rewards.DesktopPanelCount",
    "Brave.Rewards.EnabledSource",
    "Brave.Rewards.MobileConversion",
    "Brave.Rewards.MobilePanelCount",
    "Brave.Rewards.TipsState.2",
    "Brave.Rewards.ToolbarButtonTrigger",
    "Brave.Rewards.WalletBalance.3",
    "Brave.Rewards.WalletState",
    "Brave.Savings.BandwidthSavingsMB",
    "Brave.Search.Promo.BannerB",
    "Brave.Search.Promo.BannerC",
    "Brave.Search.Promo.BannerD",
    "Brave.Search.Promo.Button",
    "Brave.Search.Promo.DDGBannerA",
    "Brave.Search.Promo.DDGBannerB",
    "Brave.Search.Promo.DDGBannerC",
    "Brave.Search.Promo.DDGBannerD",
    "Brave.Search.Promo.NewTabPage",
    "Brave.Search.QueriesBeforeChurn",
    "Brave.Search.SwitchEngine",
    "Brave.Search.WebDiscoveryAndAds",
    "Brave.Search.WebDiscoveryEnabled",
    "Brave.Shields.AdBlockSetting",
    "Brave.Shields.AllowScriptOnce",
    "Brave.Shields.CookieListEnabled",
    "Brave.Shields.CookieListPrompt",
    "Brave.Shields.DomainAdsSettingsAboveGlobal",
    "Brave.Shields.DomainAdsSettingsBelowGlobal",
    "Brave.Shields.DomainFingerprintSettingsAboveGlobal",
    "Brave.Shields.DomainFingerprintSettingsBelowGlobal",
    "Brave.Shields.FingerprintBlockSetting",
    "Brave.Shields.UsageStatus",
    "Brave.Sidebar.Enabled",
    "Brave.Sidebar.SettingChange.SidebarEnabledA",
    "Brave.Sidebar.SettingChange.SidebarEnabledB",
    "Brave.SpeedReader.Enabled",
    "Brave.SpeedReader.ToggleCount",
    "Brave.Sync.ProgressTokenEverReset",
    "Brave.Sync.Status.2",
    "Brave.Today.ClickCardDepth",
    "Brave.Today.LastUsageTime",
    "Brave.Today.NewUserReturning",
    "Brave.Today.NonRewardsAdViews",
    "Brave.Today.RewardsAdViews",
    "Brave.Today.SidebarFilterUsages",
    "Brave.Today.WeeklyAddedDirectFeedsCount",
    "Brave.Today.WeeklySessionCount",
    "Brave.Today.WeeklyTotalCardClicks",
    "Brave.Today.WeeklyTotalCardViews",
    "Brave.Toolbar.FrequentMenuGroup",
    "Brave.Toolbar.MenuDismissRate",
    "Brave.Toolbar.MenuOpens",
    "Brave.VPN.DaysInMonthUsed",
    "Brave.VPN.LastUsageTime",
    "Brave.VPN.NewUserReturning",
    "Brave.VerticalTabs.GroupTabs",
    "Brave.VerticalTabs.OpenTabs",
    "Brave.VerticalTabs.PinnedTabs",
    "Brave.Wallet.ActiveBtcAccounts",
    "Brave.Wallet.ActiveEthAccounts",
    "Brave.Wallet.ActiveFilAccounts",
    "Brave.Wallet.ActiveSolAccounts",
    "Brave.Wallet.ActiveZecAccounts",
    "Brave.Wallet.BtcTransactionSent",
    "Brave.Wallet.EthProvider.4",
    "Brave.Wallet.EthTransactionSent",
    "Brave.Wallet.FilTransactionSent",
    "Brave.Wallet.KeyringCreated",
    "Brave.Wallet.LastUsageTime",
    "Brave.Wallet.NFTCount",
    "Brave.Wallet.NFTDiscoveryEnabled",
    "Brave.Wallet.NFTNewUser",
    "Brave.Wallet.NewUserBalance",
    "Brave.Wallet.NewUserReturning",
    "Brave.Wallet.OnboardingConversion.3",
    "Brave.Wallet.SolProvider.2",
    "Brave.Wallet.SolTransactionSent",
    "Brave.Wallet.UsageWeekly",
    "Brave.Wallet.ZecTransactionSent",
    "Brave.WebTorrent.UsageWeekly",
    "Brave.Webcompat.UISource",
    "Brave.Welcome.InteractionStatus.2",
});

inline constexpr auto kCollectedSlowHistograms =
  base::MakeFixedFlatSet<std::string_view>(base::sorted_unique,{
    "Brave.AIChat.ContextMenu.LastUsageTime",
    "Brave.AIChat.LastUsageTime",
    "Brave.AIChat.UsageMonthly",
    "Brave.Accessibility.DisplayZoomEnabled",
    "Brave.Autofill.PaymentMethodPresent",
    "Brave.Core.DocumentsDirectorySizeMB",
    "Brave.Core.PrimaryLang",
    "Brave.Core.ProfileCount",
    "Brave.Core.UsageMonthly",
    "Brave.General.BottomBarLocation",
    "Brave.P3A.TestSlowMetric",
    "Brave.Playlist.LastUsageTime",
    "Brave.PrivacyHub.IsEnabled",
    "Brave.PrivacyHub.Views",
    "Brave.ReaderMode.NumberReaderModeActivated",
    "Brave.RequestOTR.InterstitialDuration",
    "Brave.RequestOTR.InterstitialShown",
    "Brave.RequestOTR.SessionCount",
    "Brave.Rewards.PageViewCount",
    "Brave.Rewards.RecurringTip",
    "Brave.Rewards.TipsSent.2",
    "Brave.Shields.FilterLists",
    "Brave.Shields.ForgetFirstParty",
    "Brave.Sync.EnabledTypes",
    "Brave.Sync.SyncedObjectsCount.2",
    "Brave.Today.ChannelCount.2",
    "Brave.Today.DirectFeedsTotal.3",
    "Brave.Today.PublisherCount.2",
    "Brave.Today.UsageMonthly",
    "Brave.Toolbar.ForwardNavigationAction",
    "Brave.Wallet.UsageMonthly",
});

inline constexpr auto kCollectedExpressHistograms =
  base::MakeFixedFlatSet<std::string_view>(base::sorted_unique,{
    "Brave.AIChat.UsageDaily.2",
    "Brave.AIChat.UsageDaily.SidebarEnabledA",
    "Brave.AIChat.UsageDaily.SidebarEnabledB",
    "Brave.Core.UsageDaily",
    "Brave.DayZero.A.InstallTime",
    "Brave.DayZero.B.InstallTime",
    "Brave.Rewards.EnabledInstallationTime",
    "Brave.Search.BraveDaily",
    "Brave.Search.DefaultEngine.4",
    "Brave.Today.IsEnabled",
    "Brave.Today.UsageDaily",
    "Brave.Uptime.BrowserOpenTime.2",
    "Brave.Wallet.UsageDaily",
    "creativeInstanceId.total.count",
});

// List of metrics that should only be sent once per latest histogram update.
// Once the metric value has been sent, the value will be removed from the log store.
inline constexpr auto kEphemeralHistograms =
  base::MakeFixedFlatSet<std::string_view>(base::sorted_unique,{
    "Brave.AIChat.AcquisitionSource",
    "Brave.AIChat.AvgPromptCount",
    "Brave.AIChat.ChatCount",
    "Brave.AIChat.ContextMenu.FreeUsages",
    "Brave.AIChat.ContextMenu.LastUsageTime",
    "Brave.AIChat.ContextMenu.MostUsedAction",
    "Brave.AIChat.ContextMenu.PremiumUsages",
    "Brave.AIChat.LastUsageTime",
    "Brave.AIChat.OmniboxOpens",
    "Brave.AIChat.OmniboxWeekCompare",
    "Brave.AIChat.UsageDaily.2",
    "Brave.AIChat.UsageDaily.SidebarEnabledA",
    "Brave.AIChat.UsageDaily.SidebarEnabledB",
    "Brave.AIChat.UsageMonthly",
    "Brave.AIChat.UsageWeekly",
    "Brave.AIChat.UsageWeekly.SidebarEnabledA",
    "Brave.AIChat.UsageWeekly.SidebarEnabledB",
    "Brave.Core.FailedHTTPSUpgrades.2",
    "Brave.DayZero.A.InstallTime",
    "Brave.DayZero.B.InstallTime",
    "Brave.Playlist.FirstTimeOffset",
    "Brave.Playlist.UsageDaysInWeek",
    "Brave.PrivacyHub.Views",
    "Brave.RequestOTR.InterstitialDuration",
    "Brave.Rewards.DesktopPanelCount",
    "Brave.Rewards.EnabledInstallationTime",
    "Brave.Rewards.EnabledSource",
    "Brave.Rewards.MobileConversion",
    "Brave.Rewards.MobilePanelCount",
    "Brave.Rewards.PageViewCount",
    "Brave.Rewards.RecurringTip",
    "Brave.Rewards.TipsSent.2",
    "Brave.Rewards.ToolbarButtonTrigger",
    "Brave.Search.BraveDaily",
    "Brave.Search.QueriesBeforeChurn",
    "Brave.Shields.AllowScriptOnce",
    "Brave.Today.ChannelCount.2",
    "Brave.Today.ClickCardDepth",
    "Brave.Today.DirectFeedsTotal.3",
    "Brave.Today.IsEnabled",
    "Brave.Today.PublisherCount.2",
    "Brave.Today.SidebarFilterUsages",
    "Brave.Today.UsageDaily",
    "Brave.Today.UsageMonthly",
    "Brave.Today.WeeklyTotalCardClicks",
    "Brave.Uptime.BrowserOpenTime.2",
    "Brave.VerticalTabs.GroupTabs",
    "Brave.VerticalTabs.OpenTabs",
    "Brave.VerticalTabs.PinnedTabs",
    "Brave.Wallet.NFTCount",
    "Brave.Wallet.NFTNewUser",
    "Brave.Wallet.NewUserBalance",
    "Brave.Wallet.OnboardingConversion.3",
    "Brave.Wallet.UsageDaily",
    "Brave.Wallet.UsageMonthly",
    "Brave.Wallet.UsageWeekly",
    "Brave.WebTorrent.UsageWeekly",
    "Brave.Webcompat.UISource",
});

// List of metrics that should only be via STAR/Constellation.
// TODO(djandries): remove this once JSON deprecation is complete
inline constexpr auto kConstellationOnlyHistograms =
  base::MakeFixedFlatSet<std::string_view>(base::sorted_unique,{
    "Brave.Core.PrimaryLang",
    "Brave.DayZero.A.InstallTime",
    "Brave.DayZero.B.InstallTime",
});

// List of metrics which will include the stored refcode when transmitted
// via the STAR/Constellation protocol.
inline constexpr auto kHistogramsWithRefcodeIncluded =
  base::MakeFixedFlatSet<std::string_view>(base::sorted_unique,{
    "Brave.DayZero.A.InstallTime",
    "Brave.DayZero.B.InstallTime",
});

// clang-format on

}  // namespace p3a

#endif  // BRAVE_COMPONENTS_P3A_METRIC_NAMES_H_
